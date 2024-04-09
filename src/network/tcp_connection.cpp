#include "lamagotchi/network/tcp_connection.h"

#include <iomanip>
#include <iostream>

namespace Network
{

TcpConnection::TcpConnection(tcp::socket&& socket) : m_socket(std::move(socket))
{
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

void TcpConnection::post(uint8_t* data, uint16_t length)
{
    m_outcomingData.push({data, length});
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

                               self->printPacket(data.get(), self->m_incomingDataLength);
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

    io::async_write(m_socket, io::buffer(data, length),
                    [self = shared_from_this()](errorCode ec, size_t bytesTransferred) {
                        if (ec)
                        {
                            std::cerr << "Failed to send data. " << ec.what() << '\n';
                            // TODO: handle error.
                            return;
                        }
                        if (!self->m_outcomingData.empty())
                        {
                            self->asyncWrite();
                        }
                    });
}

void TcpConnection::printPacket(const uint8_t* const data, uint16_t length) const
{
    std::cout << std::hex << std::setfill('0');
    for (int i = 0; i < length; ++i)
    {
        if (i % 0x10 == 0)
        {
            std::cout << "\n0x" << std::setw(2) << static_cast<uint32_t>(i) << " | ";
        }

        std::cout << std::setw(2) << static_cast<uint32_t>(data[i]);

        if (i != 0 && (i + 1) % 4 == 0)
            std::cout << '\t';

        else
            std::cout << ' ';
    }
    std::cout << '\n';
}

} // namespace Network
