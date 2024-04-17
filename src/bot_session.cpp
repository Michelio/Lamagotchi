#include "lamagotchi/bot_session.h"
#include "lamagotchi/network/gameplay_handler.h"
#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/game/protocol_version.hpp"
#include "lamagotchi/network/packets/game/request_auth.hpp"
#include "lamagotchi/network/packets/game/request_enter_world.hpp"
#include "lamagotchi/network/packets/game/request_manor_list.hpp"
#include "lamagotchi/network/packets/game/request_select_char.hpp"
#include "lamagotchi/network/packets/login/gameguard_auth.hpp"
#include "lamagotchi/network/packets/login/init.hpp"
#include "lamagotchi/network/packets/login/login_ok.hpp"
#include "lamagotchi/network/packets/login/play_ok.hpp"
#include "lamagotchi/network/packets/login/request_gg_auth.hpp"
#include "lamagotchi/network/packets/login/request_login_auth.hpp"
#include "lamagotchi/network/packets/login/request_server_list.hpp"
#include "lamagotchi/network/packets/login/request_server_login.hpp"
#include "lamagotchi/network/packets/login/server_list.hpp"

namespace Lamagotchi
{

using namespace Network::Packets;

BotSession::BotSession(ConnectionPtr connection, std::string_view login, std::string_view password)
    : m_connection(connection), m_login(login), m_password(password), m_handler(new LoginHandler)
{
    auto newOnReadHandler = [this](uint8_t* data) {
        auto packet = m_handler->deserialize(data);

        switch (packet->type)
        {
        case 0x00: {
            uint16_t length = 3 + m_login.size() * 2 + m_sessionKey.size() + 6;
            RequestAuth response{length};
            response.sessionKey = m_sessionKey;
            std::vector<uint8_t> wlogin(m_login.size() * 2);
            for (uint16_t i = 0; i < m_login.size(); ++i)
            {
                *std::bit_cast<uint16_t*>(&wlogin[i * 2]) = m_login[i];
            }
            response.login = wlogin;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0x13: {
            RequestSelectChar response;
            response.charNum = 0;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0x15: {
            RequestManorList response;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0xfe: {
            RequestEnterWorld response;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        default:
            break;
        }
    };

    m_connection->onReadHandler = [this, newOnReadHandler](uint8_t* data) {
        auto packet = m_handler->deserialize(data);

        switch (packet->type)
        {
        case 0x00: {
            RequestGGAuth response;
            response.sessionId = std::bit_cast<Init*>(packet.get())->sessionId;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0x03: {
            RequestServerList response;
            response.sessionKey = std::bit_cast<LoginOk*>(packet.get())->sessionKey;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0x04: {
            RequestServerLogin response;
            response.serverId = std::bit_cast<ServerList*>(packet.get())->servers[0].id;
            m_ip = std::bit_cast<ServerList*>(packet.get())->servers[0].ip;
            m_port = std::bit_cast<ServerList*>(packet.get())->servers[0].port;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        case 0x07: {
            ProtocolVersion response;
            std::array<uint8_t, 0x08> sessionKey1 = dynamic_cast<LoginHandler*>(m_handler.get())->getSessionKey();
            std::array<uint8_t, 0x08> sessionKey2 = std::bit_cast<PlayOk*>(packet.get())->sessionKey;
            std::memcpy(m_sessionKey.data(), sessionKey2.data() + 4, 0x04);
            std::memcpy(m_sessionKey.data() + 4, sessionKey2.data(), 0x04);
            std::memcpy(m_sessionKey.data() + 8, sessionKey1.data(), 0x08);

            GameplayHandler::init();
            m_handler.reset(new GameplayHandler);
            DataPtr data = m_handler->serialize(response);

            m_connection->stop();
            m_connection->onReconnectHandler(m_connection, m_ip, m_port);
            m_connection->onReadHandler = newOnReadHandler;
            m_connection->post(data, response.length);
            break;
        }
        case 0x0b: {
            RequestLoginAuth response;
            response.login = m_login;
            response.password = m_password;
            response.ggKey = std::bit_cast<GameguardAuth*>(packet.get())->ggKey;
            DataPtr data = m_handler->serialize(response);
            m_connection->post(data, response.length);
            break;
        }
        default:
            break;
        }
    };
    m_connection->start();
}

} // namespace Lamagotchi
