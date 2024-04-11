#ifndef GAME_GUARD_AUTH_H
#define GAME_GUARD_AUTH_H

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct GameGuardAuth : Packet
{
    GameGuardAuth(uint8_t* data, uint16_t length) : Packet(length, 0x0b)
    {
    }
};

} // namespace Packets
} // namespace Network

#endif // GAME_GUARD_AUTH_H
