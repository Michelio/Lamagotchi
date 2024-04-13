#ifndef REQUEST_SERVER_LOGIN_HPP
#define REQUEST_SERVER_LOGIN_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct RequestServerLogin : Packet
{
    explicit RequestServerLogin(uint8_t type, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint8_t serverId = 0x00;
};

} // namespace Packets
} // namespace Network

#endif // REQUEST_SERVER_LOGIN_HPP
