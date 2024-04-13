#ifndef REQUEST_SERVER_LIST_HPP
#define REQUEST_SERVER_LIST_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct RequestServerList : Packet
{
    explicit RequestServerList(uint8_t type = 0x05, uint16_t length = 0x00) : Packet{type, length}
    {
    }
};

} // namespace Packets
} // namespace Network

#endif // REQUEST_SERVER_LIST_HPP
