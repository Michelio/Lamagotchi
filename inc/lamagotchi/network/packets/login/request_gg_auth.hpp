#ifndef REQUEST_GG_AUTH_HPP
#define REQUEST_GG_AUTH_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestGGAuth : Packet
{
    RequestGGAuth(uint16_t length = 0x2a, uint8_t type = 0x07) : Packet{length, type}
    {
    }

    uint32_t sessionId;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_GG_AUTH_HPP
