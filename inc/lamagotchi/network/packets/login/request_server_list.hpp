#ifndef REQUEST_SERVER_LIST_HPP
#define REQUEST_SERVER_LIST_HPP

#include "network/packets/packet.hpp"

#include <array>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestServerList : Packet
{
    explicit RequestServerList(uint16_t length = 0x22, uint8_t type = 0x05) : Packet{length, type}
    {
    }
    std::array<uint8_t, 0x08> sessionKey = {};
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_SERVER_LIST_HPP
