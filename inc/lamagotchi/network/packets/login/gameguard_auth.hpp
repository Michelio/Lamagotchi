#ifndef GAMEGUARD_AUTH_H
#define GAMEGUARD_AUTH_H

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct GameguardAuth : Packet
{
    explicit GameguardAuth(uint16_t length, uint8_t type) : Packet(length, type)
    {
    }

    uint32_t ggKey = 0;
};

} // namespace Packets
} // namespace Network

#endif // GAMEGUARD_AUTH_H
