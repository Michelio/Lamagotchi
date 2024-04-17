#ifndef REQUEST_SELECT_CHAR_HPP
#define REQUEST_SELECT_CHAR_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestSelectChar : Packet
{
    explicit RequestSelectChar(uint16_t length = 0x15, uint8_t type = 0x0d) : Packet{length, type}
    {
    }
    uint32_t charNum = 0;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_SELECT_CHAR_HPP
