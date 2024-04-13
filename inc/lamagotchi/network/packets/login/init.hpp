#ifndef INIT_HPP
#define INIT_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>

namespace Network
{

namespace Packets
{

struct Init : Packet
{
    explicit Init(uint8_t type = 0x00, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint32_t sessionId = 0x00;
    std::array<uint8_t, 0x10> bfKey = {};
    std::array<uint8_t, 0x80> rsaKey = {};
};

} // namespace Packets
} // namespace Network

#endif // INIT_HPP
