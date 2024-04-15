#ifndef REQUEST_SERVER_LOGIN_HPP
#define REQUEST_SERVER_LOGIN_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct RequestServerLogin : Packet
{
    explicit RequestServerLogin(uint16_t length = 0x00, uint8_t type = 0x02) : Packet{length, type}
    {
    }

    uint8_t serverId = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // REQUEST_SERVER_LOGIN_HPP
