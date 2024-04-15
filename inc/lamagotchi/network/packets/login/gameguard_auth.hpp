#ifndef GAMEGUARD_AUTH_HPP
#define GAMEGUARD_AUTH_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct GameguardAuth : Packet
{
    explicit GameguardAuth(uint16_t length = 0x22, uint8_t type = 0x0b) : Packet{length, type}
    {
    }

    uint32_t ggKey = 0;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // GAMEGUARD_AUTH_HPP
