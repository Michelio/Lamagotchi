#ifndef INIT_HPP
#define INIT_HPP

#include "network/packets/packet.hpp"

#include <array>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct Init : Packet
{
    explicit Init(uint16_t length = 0x00, uint8_t type = 0x00) : Packet{length, type}
    {
    }

    uint32_t sessionId = 0x00;
    std::array<uint8_t, 0x10> bfKey = {};
    std::array<uint8_t, 0x80> rsaKey = {};
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // INIT_HPP
