#ifndef PLAY_OK_HPP
#define PLAY_OK_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>

namespace Network
{

namespace Packets
{

struct PlayOk : Packet
{
    explicit PlayOk(uint8_t type, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    std::array<uint8_t, 0x08> sessionKey = {};
};

} // namespace Packets
} // namespace Network

#endif // PLAY_OK_HPP
