#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <lamagotchi/containers/thread_safe_queue.hpp>

#include <boost/asio.hpp>

namespace Network
{

using namespace Containers;
namespace io = boost::asio;
using tcp = io::ip::tcp;
using errorCode = boost::system::error_code;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
<<<<<<< Updated upstream
    explicit TcpConnection(tcp::socket&& socket);
    void start();
    void stop();
    void post(uint8_t* data, uint16_t length);
=======
    using DataPtr = std::shared_ptr<uint8_t[]>;
    using ConnectionPtr = std::shared_ptr<TcpConnection>;

    explicit TcpConnection(tcp::socket&& socket);
    [[nodiscard]] tcp::socket& socket();
    void start();
    void stop();
    void post(DataPtr data, uint16_t length);
    std::function<void(uint8_t*)> onReadHandler;
    std::function<void(ConnectionPtr, uint32_t, uint32_t)> onReconnectHandler;
>>>>>>> Stashed changes

private:
    void asyncRead();
    void onRead();
    void asyncWrite();
    void onWrite();
    void printPacket(const uint8_t* const data, uint16_t length) const;

private:
    tcp::socket m_socket;
    uint16_t m_incomingDataLength = 0;
<<<<<<< Updated upstream
    ThreadSafeQueue<std::pair<uint8_t*, uint16_t>> m_outcomingData;
=======
    ThreadSafeQueue<std::pair<DataPtr, uint16_t>> m_outcomingData;
>>>>>>> Stashed changes
};

} // namespace Network

#endif // TCP_CONNECTION_H
