#include "lamagotchi/bot_session.h"
#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/game/protocol_version.hpp"
#include "lamagotchi/network/packets/login/gameguard_auth.hpp"
#include "lamagotchi/network/packets/login/init.hpp"
#include "lamagotchi/network/packets/login/login_ok.hpp"
#include "lamagotchi/network/packets/login/play_ok.hpp"
#include "lamagotchi/network/packets/login/request_gg_auth.hpp"
#include "lamagotchi/network/packets/login/request_login_auth.hpp"
#include "lamagotchi/network/packets/login/request_server_list.hpp"
#include "lamagotchi/network/packets/login/request_server_login.hpp"
#include "lamagotchi/network/packets/login/server_list.hpp"

#include <iostream>

namespace Lamagotchi
{

using namespace Network::Packets;

BotSession::BotSession(ConnectionPtr connection, std::string_view login, std::string_view password)
    : m_connection(connection), m_login(login), m_password(password), m_handler(new LoginHandler)
{
    m_connection->onReadHandler = [this](uint8_t* data) {
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
            // Stop socket ->
            // -> Connect to game server ->
            // -> Change packet handler ->
            // -> Start async read
            ProtocolVersion response;
            std::array<uint8_t, 0x08> sessionKey1 = dynamic_cast<LoginHandler*>(m_handler.get())->getSessionKey();
            std::array<uint8_t, 0x08> sessionKey2 = std::bit_cast<PlayOk*>(packet.get())->sessionKey;
            m_connection->stop();
            std::cout << "Disconnected from login server\n";
            m_connection->onReconnectHandler(m_connection, m_ip, m_port);

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
