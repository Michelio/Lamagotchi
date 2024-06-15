#ifndef REQUEST_MANOR_LIST_HPP
#define REQUEST_MANOR_LIST_HPP

#include "network/packets/packet.hpp"
#include <cstdint>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestManorList : Packet
{
    explicit RequestManorList(uint16_t length = 0x05, uint8_t type = 0xd0) : Packet{length, type}
    {
    }
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_MANOR_LIST_HPP
