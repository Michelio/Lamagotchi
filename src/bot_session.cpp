#include "lamagotchi/bot_session.h"
#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/login/gameguard_auth.hpp"
#include "lamagotchi/network/packets/login/init.hpp"
#include "lamagotchi/network/packets/login/request_gg_auth.hpp"
#include "lamagotchi/network/packets/login/request_login_auth.hpp"
#include "lamagotchi/network/packets/login/request_server_list.hpp"

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
            RequestGGAuth answer;
            answer.sessionId = std::bit_cast<Init*>(packet.get())->sessionId;
            DataPtr data = m_handler->serialize(answer);
            m_connection->post(data, answer.length);
            break;
        }
        case 0x03: {
            RequestServerList answer;

            DataPtr data = m_handler->serialize(answer);
            m_connection->post(data, answer.length);
            break;
        }
        case 0x0b: {
            RequestLoginAuth answer;
            answer.login = m_login;
            answer.password = m_password;
            answer.ggKey = std::bit_cast<GameguardAuth*>(packet.get())->ggKey;
            DataPtr data = m_handler->serialize(answer);
            m_connection->post(data, answer.length);
            break;
        }
        default:
            break;
        }
    };
    m_connection->start();
}

} // namespace Lamagotchi
