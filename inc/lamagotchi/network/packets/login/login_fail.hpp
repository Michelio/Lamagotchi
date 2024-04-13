#ifndef LOGIN_FAIL_HPP
#define LOGIN_FAIL_HPP

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct LoginFail : Packet
{
    LoginFail(uint8_t type, uint16_t length = 0x00) : Packet{type, length}
    {
    }

    uint8_t reason = 0x00;
};

} // namespace Packets
} // namespace Network

#endif // LOGIN_FAIL_HPP
