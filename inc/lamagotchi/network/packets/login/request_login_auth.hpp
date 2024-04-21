#ifndef REQUEST_LOGIN_AUTH_HPP
#define REQUEST_LOGIN_AUTH_HPP

#include "network/packets/packet.hpp"

#include <string>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestLoginAuth : Packet
{
    RequestLoginAuth(uint16_t length = 0xb2, uint8_t type = 0x00) : Packet{length, type}
    {
    }

    std::string login = "test";
    std::string password = "test";
    uint32_t ggKey = 0;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // !REQUEST_LOGIN_AUTH_HPP
