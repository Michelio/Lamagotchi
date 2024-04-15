#ifndef CRYPT_INIT_HPP
#define CRYPT_INIT_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct CryptInit : Packet
{
    explicit CryptInit(uint16_t length = 0x1c, uint8_t type = 0x00) : Packet{length, type}
    {
    }

    std::array<uint8_t, 0x10> key;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // CRYPT_INIT_HPP
