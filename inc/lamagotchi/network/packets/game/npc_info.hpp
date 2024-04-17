#ifndef NPC_INFO_HPP
#define NPC_INFO_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct NpcInfo : Packet
{
    explicit NpcInfo(uint16_t length, uint8_t type = 0x16) : Packet{length, type}
    {
    }

    uint32_t objectId = 0x00;
    uint32_t npcTypeid = 0x00;
    uint32_t isAttackable = 0x00;
    uint32_t x = 0x00;
    uint32_t y = 0x00;
    uint32_t z = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // NPC_INFO_HPP
