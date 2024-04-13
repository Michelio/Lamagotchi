#include "lamagotchi/bot_client.h"
#include "lamagotchi/network/login_handler.h"

#include <iostream>

namespace Lamagotchi
{

BotClient::BotClient() : m_tcpClient("192.168.88.19", 2106)
{
    Network::LoginHandler::init();
    m_tcpClient.onConnectHandler = [this](ConnectionPtr connection) {
        std::cout << "Inside onConnectHandler \n";
        this->addSession(std::move(connection));
    };
}

void BotClient::addSession(ConnectionPtr connection)
{
    m_sessions.emplace(new BotSession{connection, "test", "test"});
}

void BotClient::run()
{
    m_tcpClient.connect();
    m_tcpClient.run();
}

} // namespace Lamagotchi
