#ifndef LOGIN_FAIL_HPP
#define LOGIN_FAIL_HPP

#include "network/packets/packet.hpp"

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct LoginFail : Packet
{
    LoginFail(uint16_t length = 0x00, uint8_t type = 0x01) : Packet{length, type}
    {
    }

    uint8_t reason = 0x00;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // LOGIN_FAIL_HPP
