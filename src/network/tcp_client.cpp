#include "lamagotchi/network/tcp_client.h"
#include "lamagotchi/network/tcp_connection.h"

#include <iostream>

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
    auto t_socket = std::make_shared<tcp::socket>(m_ioContext);
    io::async_connect(*t_socket, m_endpoints, [this, socket = t_socket](errorCode ec, tcp::endpoint ep) {
        if (ec)
        {
            std::cout << "Can't connect to the server. " << ec.what() << '\n';
            // TODO: handle error.
            return;
        }

        std::cout << "Connected!!!\n";

        auto connection = std::make_shared<TcpConnection>(std::move(*socket));
        m_connections.insert(connection);
        connection->start();
    });
}

void TcpClient::run()
{
    m_ioContext.run();
}

} // namespace Network
