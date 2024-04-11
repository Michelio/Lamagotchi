#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

namespace Network
{

class PacketHandler;

namespace Packets
{
struct Packet
{
    Packet(uint16_t length, uint8_t type) : length(length), type(type)
    {
    }
    uint16_t length = 0;
    uint8_t type = 0xff;
};
} // namespace Packets

} // namespace Network

#endif // PACKET_H
