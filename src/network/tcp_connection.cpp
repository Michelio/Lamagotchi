#include "lamagotchi/network/tcp_connection.h"

#include <boost/endian.hpp>
#include <iostream>

namespace Lamagotchi
{

namespace Network
{

TcpConnection::TcpConnection(tcp::socket&& socket) : m_socket(new tcp::socket{std::move(socket)})
{
}

void TcpConnection::setSocket(tcp::socket&& socket)
{
    m_socket.reset(new tcp::socket{std::move(socket)});
}

void TcpConnection::start()
{
    asyncRead();
}

void TcpConnection::stop()
{
    errorCode ec;
    m_socket->cancel();
    m_socket->shutdown(tcp::socket::shutdown_receive, ec);

    if (ec)
    {
        std::cerr << "Failed to shut down the socket. " << ec.message() << std::endl;
        ec.clear();
    }

    m_socket->close(ec);

    if (ec)
    {
        std::cerr << "Failed to close the socket. " << ec.message() << std::endl;
        ec.clear();
    }
}

void TcpConnection::post(std::shared_ptr<uint8_t[]> data, uint16_t length)
{
    m_outcomingData.push({data, length});
    asyncWrite();
}

void TcpConnection::asyncRead()
{
    io::async_read(*m_socket, io::buffer(&m_incomingDataLength, sizeof(uint16_t)),
                   [self = shared_from_this()](errorCode ec, size_t bytesReceived) {
                       if (ec)
                       {
                           std::cout << "Failed to receive packet length. " << ec.what() << '\n';
                           // TODO: handle error.
                           self->m_socket->close();
                           return;
                       }

                       boost::endian::little_to_native_inplace(self->m_incomingDataLength);
                       DataPtr data(new uint8_t[self->m_incomingDataLength]);
                       std::memcpy(data.get(), &self->m_incomingDataLength, sizeof(uint16_t));

                       self->m_incomingDataLength -= sizeof(uint16_t);

                       io::async_read(*self->m_socket,
                                      io::buffer(data.get() + sizeof(uint16_t), self->m_incomingDataLength),
                                      [self, data](errorCode ec, size_t bytesReceived) {
                                          if (ec)
                                          {
                                              std::cerr << "Failed to read packet load. " << ec.what() << '\n';
                                              // TODO: handle error.
                                              self->m_socket->close();
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

    io::async_write(*m_socket, io::buffer(data.get(), length),
                    [self = shared_from_this()](errorCode ec, size_t bytesTransferred) {
                        if (ec)
                        {
                            std::cerr << "Failed to send data. " << ec.what() << '\n';
                            // TODO: handle error.
                            self->m_socket->close();
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
