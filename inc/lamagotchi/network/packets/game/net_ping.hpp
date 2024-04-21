#ifndef NET_PING_HPP
#define NET_PING_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct NetPing : Packet
{
    explicit NetPing(uint16_t length = 0x0f, uint8_t type = 0xa8) : Packet{length, type}
    {
    }

    uint32_t id = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // NET_PING_HPP
