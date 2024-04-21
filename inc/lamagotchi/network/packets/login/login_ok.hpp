#ifndef LOGIN_OK_HPP
#define LOGIN_OK_HPP

#include "network/packets/packet.hpp"

#include <array>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct LoginOk : Packet
{
    explicit LoginOk(uint16_t length = 0x00, uint8_t type = 0x03) : Packet{length, type}
    {
    }

    std::array<uint8_t, 0x08> sessionKey = {};
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // LOGIN_OK_HPP
