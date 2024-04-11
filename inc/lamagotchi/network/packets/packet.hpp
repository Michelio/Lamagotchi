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
    uint16_t length = 0;
    uint8_t type = 0xff;
};
} // namespace Packets

} // namespace Network

#endif // PACKET_H
