#ifndef PLAY_FAIL_HPP
#define PLAY_FAIL_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct PlayFail : Packet
{
    explicit PlayFail(uint8_t type = 0x06, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint32_t reason = 0x00;
};

} // namespace Packets
} // namespace Network

#endif // PLAY_FAIL_HPP
