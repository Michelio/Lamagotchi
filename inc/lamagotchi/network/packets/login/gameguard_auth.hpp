#ifndef GAMEGUARD_AUTH_H
#define GAMEGUARD_AUTH_H

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct GameguardAuth : Packet
{
    GameguardAuth(uint8_t* data, uint16_t length) : Packet(length, 0x0b)
    {
    }
};

} // namespace Packets
} // namespace Network

#endif // GAMEGUARD_AUTH_H
