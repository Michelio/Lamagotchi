#ifndef BOT_SESSION_H
#define BOT_SESSION_H

#include "lamagotchi/network/packet_handler.h"
#include "lamagotchi/network/tcp_connection.h"

#include <memory>

namespace Lamagotchi
{

using namespace Network;

class BotSession
{
public:
    using ConnectionPtr = std::shared_ptr<TcpConnection>;
    using PacketHandlerPtr = std::unique_ptr<PacketHandler>;

    explicit BotSession(ConnectionPtr connection, std::string_view login, std::string_view password);

private:
    PacketHandlerPtr m_handler;
    ConnectionPtr m_connection;
    std::string m_login;
    std::string m_password;
    uint32_t m_ip;
    uint32_t m_port;
    std::array<uint8_t, 0x10> m_sessionKey = {};
};

} // namespace Lamagotchi

#endif // BOT_SESSION_H
