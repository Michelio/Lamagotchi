#ifndef BOT_CLIENT_H
#define BOT_CLIENT_H

#include "bot_session.h"
#include "network/tcp_client.h"

#include <unordered_set>

namespace Lamagotchi
{

class BotClient
{
public:
    using ConnectionPtr = std::shared_ptr<TcpConnection>;
    using SessionPtr = std::shared_ptr<BotSession>;
    BotClient();
    void addSession(ConnectionPtr connection);
    void run();

private:
    std::unordered_set<SessionPtr> m_sessions;
    Network::TcpClient m_tcpClient;
};

} // namespace Lamagotchi

#endif // BOT_CLIENT_H
