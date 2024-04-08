#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <boost/asio.hpp>

namespace Network
{

namespace io = boost::asio;
using tcp = io::ip::tcp;
using errorCode = boost::system::error_code;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
    using DataHandler = std::function<void(const uint8_t*)>;
    using ErrorHandler = std::function<void(std::string_view)>;
    using Pointer = std::shared_ptr<TcpConnection>;

public:
    explicit TcpConnection(tcp::socket&& socket);
    void start();
    void stop();
    void post(const uint8_t* data, uint16_t length);

private:
    void asyncRead();
    void onRead();
    void asyncWrite();
    void onWrite();
    void printPacket(const uint8_t* const data, uint16_t length) const;

private:
    tcp::socket m_socket;
    uint16_t m_incomingDataLength = 0;
    uint16_t m_outcomingDataLength = 0;
};

} // namespace Network

#endif // TCP_CONNECTION_H
