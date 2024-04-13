#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <boost/asio.hpp>

namespace Lamagotchi
{

namespace Network
{

namespace io = boost::asio;
using tcp = io::ip::tcp;
using errorCode = boost::system::error_code;

class TcpConnection;

class TcpClient
{
public:
    using ConnectionPtr = std::shared_ptr<TcpConnection>;
    explicit TcpClient(std::string_view address, const uint32_t port);
    void connect();
    void run();
    std::function<void(ConnectionPtr)> onConnectHandler;

private:
    io::io_context m_ioContext;
    tcp::resolver::results_type m_endpoints;
    std::string m_address;
    uint32_t m_port;
};

} // namespace Network
} // namespace Lamagotchi

#endif // TCP_CLIENT_H
