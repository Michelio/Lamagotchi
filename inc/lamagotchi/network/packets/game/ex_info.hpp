#ifndef EX_INFO_HPP
#define EX_INFO_HPP

#include "network/packets/packet.hpp"

#include <vector>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct ExInfo : Packet
{
    explicit ExInfo(uint16_t length, uint8_t type = 0xfe) : Packet{length, type}
    {
    }

    uint32_t count = 0;
    std::vector<uint8_t> list;
    uint8_t subType = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // EX_INFO_HPP
