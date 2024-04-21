#ifndef REQUEST_NET_PING_HPP
#define REQUEST_NET_PING_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestNetPing : Packet
{
    explicit RequestNetPing(uint16_t length = 0x07, uint8_t type = 0xd3) : Packet{length, type}
    {
    }

    uint32_t id = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_NET_PING_HPP
