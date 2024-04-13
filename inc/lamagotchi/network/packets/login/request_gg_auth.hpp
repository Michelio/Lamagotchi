#ifndef REQUEST_GG_AUTH_HPP
#define REQUEST_GG_AUTH_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct RequestGGAuth : Packet
{
    RequestGGAuth(uint8_t type, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint32_t sessionKey;
};

} // namespace Packets
} // namespace Network

#endif // REQUEST_GG_AUTH_HPP
