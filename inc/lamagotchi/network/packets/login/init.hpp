#ifndef INIT_HPP
#define INIT_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>

namespace Network
{

namespace Packets
{
struct Init : Packet
{
    uint32_t session_key = 0x00000000;
    std::array<uint8_t, 0x10> bf_key = {};
    std::array<uint8_t, 0x80> rsa_key = {};
};

} // namespace Packets

} // namespace Network

#endif // INIT_HPP
