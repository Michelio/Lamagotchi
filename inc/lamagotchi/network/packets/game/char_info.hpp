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
    explicit CharInfo(uint16_t length, uint8_t type = 0x31) : Packet{length, type}
    {
    }

    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint32_t objectId = -1;
    std::wstring objectTitle = L"";
    std::wstring objectName = L"";
    uint32_t karma = 0;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // CHAR_INFO_HPP
