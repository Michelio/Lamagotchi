#ifndef PLAY_FAIL_HPP
#define PLAY_FAIL_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct PlayFail : Packet
{
    explicit PlayFail(uint16_t length = 0x00, uint8_t type = 0x06) : Packet{length, type}
    {
    }

    uint32_t reason = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // PLAY_FAIL_HPP
