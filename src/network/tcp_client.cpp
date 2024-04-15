#include "lamagotchi/network/tcp_client.h"
#include "lamagotchi/network/tcp_connection.h"

#include <iostream>

namespace Lamagotchi
{

namespace Network
{

TcpClient::TcpClient(std::string_view address, const uint32_t port) : m_address(address), m_port(port)
{
    tcp::resolver resolver{m_ioContext};
    m_endpoints = resolver.resolve(m_address, std::to_string(m_port));
    std::cout << m_address << ':' << m_port << '\n';
}

void TcpClient::connect()
{
    auto socket = std::make_shared<tcp::socket>(m_ioContext);
    io::async_connect(*socket, m_endpoints, [this, socket](errorCode ec, tcp::endpoint ep) {
        if (ec)
        {
            std::cout << "Can't connect to the server. " << ec.what() << '\n';
            // TODO: handle error.
            return;
        }

        std::cout << "Inside connect handler\n";
        auto connection = std::make_shared<TcpConnection>(std::move(*socket), &this->m_ioContext);
        onConnectHandler(connection);
    });

    m_ioContext.run();
}

} // namespace Network
} // namespace Lamagotchi
