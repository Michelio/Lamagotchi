#ifndef USER_INFO_HPP
#define USER_INFO_HPP

#include "network/packets/packet.hpp"
#include <string>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct UserInfo : Packet
{
    explicit UserInfo(uint16_t length, uint8_t type = 0x04) : Packet{length, type}
    {
    }

    uint32_t x = 0x00;
    uint32_t y = 0x00;
    uint32_t z = 0x00;
    uint32_t objectId = 0x00;
    std::wstring nickname = L"";
    uint32_t level = 0x00;
    uint32_t exp = 0x00;
    uint32_t STR = 0x00;
    uint32_t DEX = 0x00;
    uint32_t CON = 0x00;
    uint32_t INT = 0x00;
    uint32_t WIT = 0x00;
    uint32_t MEN = 0x00;
    uint32_t maxHP = 0x00;
    uint32_t curHP = 0x00;
    uint32_t maxMP = 0x00;
    uint32_t curMP = 0x00;
    uint32_t maxCP = 0x00;
    uint32_t curCP = 0x00;
    uint32_t skillPoints = 0x00;
    uint32_t load = 0x00;
    uint32_t maxLoad = 0x00;
    uint32_t pAttack = 0x00;
    uint32_t pAttackSpeed = 0x00;
    uint32_t pDefense = 0x00;
    uint32_t evasion = 0x00;
    uint32_t accuracy = 0x00;
    uint32_t critical = 0x00;
    uint32_t mAttack = 0x00;
    uint32_t mAttackSpeed = 0x00;
    uint32_t mDefense = 0x00;
    uint32_t pvpStatus = 0x00;
    uint32_t karma = 0x00;
    uint32_t pvpCount = 0x00;
    uint32_t pkCount = 0x00;
    uint32_t speedRun = 0x00;
    uint32_t speedWalk = 0x00;
    std::wstring title = L"";
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // USER_INFO_HPP
