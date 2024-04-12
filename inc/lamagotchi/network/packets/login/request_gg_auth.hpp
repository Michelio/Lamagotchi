#ifndef REQUEST_GG_AUTH_H
#define REQUEST_GG_AUTH_H

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct RequestGGAuth : Packet
{
    RequestGGAuth(uint16_t length, uint8_t type) : Packet(length, type)
    {
    }

    uint32_t sessionKey;
};

} // namespace Packets
} // namespace Network

#endif // REQUEST_GG_AUTH_H
