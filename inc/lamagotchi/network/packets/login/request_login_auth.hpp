#ifndef REQUEST_LOGIN_AUTH_HPP
#define REQUEST_LOGIN_AUTH_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <string>

namespace Network
{

namespace Packets
{

struct RequestLoginAuth : Packet
{
    RequestLoginAuth(uint16_t length, uint8_t type) : Packet(length, type)
    {
    }

    std::string login = "test";
    std::string password = "test";
    uint32_t ggKey = 0;
};

} // namespace Packets
} // namespace Network

#endif // !REQUEST_LOGIN_AUTH_HPP
