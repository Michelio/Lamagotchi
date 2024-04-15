#include "lamagotchi/network/tcp_client.h"
#include "lamagotchi/network/tcp_connection.h"

#include <boost/endian.hpp>
#include <iostream>

namespace Lamagotchi
{

namespace Network
{

TcpClient::TcpClient(std::string_view address, const uint32_t port) : m_address(address), m_port(port)
{
    m_endpoints = m_resolver.resolve(m_address, std::to_string(m_port));
}

void TcpClient::connect()
{
    auto socket = std::make_shared<tcp::socket>(m_ioContext);
    auto connectDeadline = std::make_shared<io::steady_timer>(m_ioContext, std::chrono::seconds{10});

    connectDeadline->async_wait([socket](errorCode ec) {
        if (ec)
        {
            if (ec != io::error::operation_aborted)
            {
                std::cerr << "Timer failed. " << ec.what() << '\n';
            }
            // TODO: handle error.
            return;
        }

        std::cout << "Can't connect to the server. Out of time.\n";
        socket->shutdown(tcp::socket::shutdown_both);
        socket->cancel();
    });

    io::async_connect(*socket, m_endpoints, [this, socket, connectDeadline](errorCode ec, tcp::endpoint ep) {
        connectDeadline->cancel();
        if (ec)
        {
            if (ec != io::error::operation_aborted)
            {
                std::cerr << "Can't connect to the server. " << ec.what() << '\n';
            }
            // TODO: handle error.
            return;
        }

        std::cout << "Connected to: " << ep.address() << ':' << ep.port() << '\n';
        auto connection = std::make_shared<TcpConnection>(std::move(*socket));
        connection->onReconnectHandler = [this](ConnectionPtr connection, uint32_t ip, uint32_t port) {
            boost::endian::native_to_big_inplace(ip);
            io::ip::address t_ip = io::ip::address_v4(ip);

            auto reconnectDeadline = std::make_shared<io::steady_timer>(m_ioContext, std::chrono::seconds{10});
            reconnectDeadline->async_wait([connection](errorCode ec) {
                if (ec)
                {
                    if (ec != io::error::operation_aborted)
                    {
                        std::cerr << "Timer failed. " << ec.what() << '\n';
                    }
                    // TODO: handle error.
                    return;
                }

                std::cout << "Can't reconnect to the server. Out of time.\n";
                connection->stop();
            });

            io::async_connect(connection->socket(), m_resolver.resolve(t_ip.to_string(), std::to_string(port)),
                              [connection, reconnectDeadline](errorCode ec, tcp::endpoint ep) {
                                  reconnectDeadline->cancel();
                                  if (ec)
                                  {
                                      if (ec != io::error::operation_aborted)
                                      {
                                          std::cerr << "Can't reconnect to the server. " << ec.what() << '\n';
                                      }
                                      // TODO: handle error.
                                      return;
                                  }

                                  std::cout << "Reconnected to: " << ep.address() << ':' << ep.port() << '\n';
                                  connection->start();
                              });
        };
        onConnectHandler(connection);
    });

    m_ioContext.run();
}

} // namespace Network
} // namespace Lamagotchi
