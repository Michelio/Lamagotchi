#ifndef BOT_CLIENT_H
#define BOT_CLIENT_H

#include "bot_session.h"
#include "network/tcp_client.h"

#include <QObject>
#include <unordered_set>

namespace Lamagotchi
{

class BotClient : public QObject
{
public:
    using ConnectionPtr = std::shared_ptr<TcpConnection>;
    using SessionPtr = std::shared_ptr<BotSession>;
    BotClient();
    void addSession(ConnectionPtr connection, std::string_view login, std::string_view password);
    void run();

private:
    std::unordered_set<SessionPtr> m_sessions;
    Network::TcpClient m_tcpClient;

public slots:
    void onCredentialsReady(std::string login, std::string password);
};

} // namespace Lamagotchi

#endif // BOT_CLIENT_H
