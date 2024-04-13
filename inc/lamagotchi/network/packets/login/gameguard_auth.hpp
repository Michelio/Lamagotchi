#ifndef GAMEGUARD_AUTH_HPP
#define GAMEGUARD_AUTH_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct GameguardAuth : Packet
{
    explicit GameguardAuth(uint8_t type = 0x0b, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint32_t ggKey = 0;
};

} // namespace Packets
} // namespace Network

#endif // GAMEGUARD_AUTH_HPP
