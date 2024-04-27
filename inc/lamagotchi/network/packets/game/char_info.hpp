#ifndef CHAR_INFO_HPP
#define CHAR_INFO_HPP

#include "network/packets/packet.hpp"

#include <string>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct CharInfo : Packet
{
    explicit CharInfo(uint16_t length, uint8_t type = 0x03) : Packet{length, type}
    {
    }

    uint32_t x = 0x00;
    uint32_t y = 0x00;
    uint32_t z = 0x00;
    uint32_t objectId = 0x00;
    std::wstring name = L"";
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // CHAR_INFO_HPP
