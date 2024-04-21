#ifndef CHAR_LIST_HPP
#define CHAR_LIST_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct CharList : Packet
{
    explicit CharList(uint16_t length, uint8_t type = 0x13) : Packet{length, type}
    {
    }

    uint32_t count = 0;
    // std::vector<uint32_t> characters;
    // TODO: parse info about characters on account.
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // CHAR_LIST_HPP
