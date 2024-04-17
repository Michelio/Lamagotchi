#ifndef REQUEST_AUTH_HPP
#define REQUEST_AUTH_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>
#include <vector>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestAuth : Packet
{
    explicit RequestAuth(uint16_t length, uint8_t type = 0x08) : Packet{length, type}
    {
    }

    std::array<uint8_t, 0x10> sessionKey = {};
    std::vector<uint8_t> login;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_AUTH_HPP
