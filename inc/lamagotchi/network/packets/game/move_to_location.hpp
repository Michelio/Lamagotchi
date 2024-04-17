#ifndef MOVE_TO_LOCATION_HPP
#define MOVE_TO_LOCATION_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct MoveToLocation : Packet
{
    explicit MoveToLocation(uint16_t length = 0x1f, uint8_t type = 0x01) : Packet{length, type}
    {
    }

    uint32_t objectId = 0x00;
    uint32_t destX = 0x00;
    uint32_t destY = 0x00;
    uint32_t destZ = 0x00;
    uint32_t sourceX = 0x00;
    uint32_t sourceY = 0x00;
    uint32_t sourceZ = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // MOVE_TO_LOCATION_HPP
