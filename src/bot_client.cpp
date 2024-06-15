#include "bot_client.h"
#include "network/login_handler.h"

namespace Lamagotchi
{

BotClient::BotClient() : m_tcpClient("149.56.28.81", 2106)
{
    Network::LoginHandler::init();
}

void BotClient::addSession(ConnectionPtr connection, std::string_view login, std::string_view password)
{
    m_sessions.emplace(new BotSession{connection, login, password});
}

void BotClient::run()
{
    m_tcpClient.run();
}

void BotClient::onCredentialsReady(std::string login, std::string password)
{
    m_tcpClient.onConnectHandler = [this, login, password](ConnectionPtr connection) {
        this->addSession(connection, login, password);
    };
    m_tcpClient.connect();
}

} // namespace Lamagotchi
