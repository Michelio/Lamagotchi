#ifndef REQUEST_ENTER_WORLD_HPP
#define REQUEST_ENTER_WORLD_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestEnterWorld : Packet
{
    explicit RequestEnterWorld(uint16_t length = 0x6b, uint8_t type = 0x03) : Packet{length, type}
    {
    }
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_ENTER_WORLD_HPP
