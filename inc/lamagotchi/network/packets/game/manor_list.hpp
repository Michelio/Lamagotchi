#ifndef MANOR_LIST_HPP
#define MANOR_LIST_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <vector>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct ManorList : Packet
{
    explicit ManorList(uint16_t length, uint8_t type = 0xfe) : Packet{length, type}
    {
    }

    uint32_t count = 0;
    std::vector<uint8_t> list;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // MANOR_LIST_HPP
