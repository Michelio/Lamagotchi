#include "lamagotchi/bot_session.h"
#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/packet.hpp"

#include <iostream>

namespace Lamagotchi
{

BotSession::BotSession(ConnectionPtr connection, std::string_view login, std::string_view password)
    : m_connection(connection), m_login(login), m_password(password), m_handler(new LoginHandler)
{
    m_connection->onReadHandler = [this](uint8_t* data) {
        std::cout << "Inside onReadHandler call\n";
        auto packet = m_handler->deserialize(data);

        switch (packet->type)
        {
        case 0x00:
            std::cout << "Received init packet\n";
            break;
        default:
            break;
        }
    };
    m_connection->start();
}

} // namespace Lamagotchi
