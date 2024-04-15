#include "lamagotchi/network/tcp_connection.h"

#include <iomanip>
#include <boost/endian.hpp>
#include <iostream>

namespace Lamagotchi
{

namespace Network
{

TcpConnection::TcpConnection(tcp::socket&& socket, io::io_context* context)
    : m_socket(std::move(socket)), m_context(context)
{
}

tcp::socket& TcpConnection::socket()
{
    return m_socket;
}

void TcpConnection::start()
{
    asyncRead();
}

void TcpConnection::stop()
{
    m_socket.shutdown(tcp::socket::shutdown_both);
    m_socket.close();
}

void TcpConnection::post(std::shared_ptr<uint8_t[]> data, uint16_t length)
{
    m_outcomingData.push({data, length});
    std::cout << "Posting data.\n";
    asyncWrite();
}

void TcpConnection::asyncRead()
{
    io::async_read(
        m_socket, io::buffer(&m_incomingDataLength, sizeof(m_incomingDataLength)),
        [this](errorCode ec, size_t bytesReceived) {
            if (ec)
            {
                std::cout << "Failed to receive packet length. " << ec.what() << '\n';
                // TODO: handle error.
                return;
            }

            std::shared_ptr<uint8_t[]> data(new uint8_t[m_incomingDataLength], std::default_delete<uint8_t[]>());
            std::memcpy(data.get(), &m_incomingDataLength, sizeof(m_incomingDataLength));


            m_incomingDataLength -= sizeof(m_incomingDataLength);

            io::async_read(m_socket, io::buffer(data.get() + sizeof(m_incomingDataLength), m_incomingDataLength),
                           [self = shared_from_this(), data](errorCode ec, size_t bytesReceived) {
                               if (ec)
                               {
                                   std::cerr << "Failed to read packet load. " << ec.what() << '\n';
                                   // TODO: handle error.
                                   return;
                               }
                       boost::endian::little_to_native_inplace(self->m_incomingDataLength);
                       self->m_incomingDataLength -= sizeof(uint16_t);

                       io::async_read(self->m_socket,
                                      io::buffer(data.get() + sizeof(uint16_t), self->m_incomingDataLength),
                                      [self, data](errorCode ec, size_t bytesReceived) {
                                          if (ec)
                                          {
                                              std::cerr << "Failed to read packet load. " << ec.what() << '\n';
                                              // TODO: handle error.
                                              return;
                                          }

                                          self->onReadHandler(data.get());
                                          self->onRead();
                                      });
                   });
}

void TcpConnection::onRead()
{
    asyncRead();
}

void TcpConnection::asyncWrite()
{
    auto [data, length] = m_outcomingData.pop();

    io::async_write(m_socket, io::buffer(data.get(), length),
                    [self = shared_from_this()](errorCode ec, size_t bytesTransferred) {
                        if (ec)
                        {
                            std::cerr << "Failed to send data. " << ec.what() << '\n';
                            // TODO: handle error.
                            return;
                        }

                        self->onWrite();
                    });
}

void TcpConnection::onWrite()
{
    if (!m_outcomingData.empty())
    {
        asyncWrite();
    }
}

} // namespace Network
} // namespace Lamagotchi
