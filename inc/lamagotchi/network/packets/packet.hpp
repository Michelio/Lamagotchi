#ifndef PACKET_HPP
#define PACKET_HPP

#include <stdint.h>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct Packet
{
    explicit Packet(uint8_t type, uint16_t length = 0x00) : length(length), type(type)
    {
    }

    uint16_t length = 0;
    uint8_t type;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // PACKET_HPP
