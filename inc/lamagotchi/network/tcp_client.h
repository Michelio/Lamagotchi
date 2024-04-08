#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <boost/asio.hpp>
#include <unordered_set>

namespace Network
{

namespace io = boost::asio;
using tcp = io::ip::tcp;
using errorCode = boost::system::error_code;

class TcpConnection;

class TcpClient
{
public:
    explicit TcpClient(std::string_view address, const uint32_t port);
    void connect();
    void run();
    void cancel();

private:
    io::io_context m_ioContext;
    tcp::resolver::results_type m_endpoints;
    std::unordered_set<std::shared_ptr<TcpConnection>> m_connections;
    std::string m_address;
    uint32_t m_port;
};

} // namespace Network

#endif // TCP_CLIENT_H
