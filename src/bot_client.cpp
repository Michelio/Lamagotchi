#include "bot_client.h"
#include "network/login_handler.h"

namespace Lamagotchi
{

BotClient::BotClient() : m_tcpClient("192.168.88.19", 2106)
{
    Network::LoginHandler::init();
    m_tcpClient.onConnectHandler = [this](ConnectionPtr connection) { this->addSession(connection); };
    // m_tcpClient.connect();
}

void BotClient::addSession(ConnectionPtr connection)
{
    m_sessions.emplace(new BotSession{connection, "qweewqqweewq", "ewqqweewqqweewq!"});
}

void BotClient::run()
{
    m_tcpClient.run();
}

} // namespace Lamagotchi
