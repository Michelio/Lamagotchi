#ifndef CHAR_SELECTED_HPP
#define CHAR_SELECTED_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct CharSelected : Packet
{
    explicit CharSelected(uint16_t length, uint8_t type = 0x15) : Packet{length, type}
    {
    }
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // CHAR_SELECTED_HPP
