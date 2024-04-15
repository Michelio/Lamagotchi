#ifndef PLAY_OK_HPP
#define PLAY_OK_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct PlayOk : Packet
{
    explicit PlayOk(uint8_t type = 0x07, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    std::array<uint8_t, 0x08> sessionKey = {};
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // PLAY_OK_HPP
