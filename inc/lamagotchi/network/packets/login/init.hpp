#ifndef INIT_HPP
#define INIT_HPP

#include "lamagotchi/network/packets/packet.hpp"

#include <array>
#include <cstring>

namespace Network
{

namespace Packets
{

struct Init : Packet
{
    explicit Init(uint8_t* data, uint16_t length) : Packet(length, 0x00)
    {
        uint16_t i = length - 8;
        uint32_t k = *std::bit_cast<uint32_t*>(data + length - 8);

        while (i >= 6 && i < length)
        {
            *std::bit_cast<uint32_t*>(&data[i]) = *std::bit_cast<uint32_t*>(&data[i]) ^ k;
            k -= *std::bit_cast<uint32_t*>(&data[i]);
            i -= 4;
        }

        uint16_t offset = sizeof(uint16_t) + sizeof(uint8_t);
        std::memcpy(&this->session_key, data + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t) * 2;
        std::memcpy(this->rsa_key.data(), data + offset, 0x80);
        offset += 0x80 + sizeof(uint32_t) * 4;
        std::memcpy(this->bf_key.data(), data + offset, 0x10);
    }

    uint32_t session_key = 0x00;
    std::array<uint8_t, 0x10> bf_key = {};
    std::array<uint8_t, 0x80> rsa_key = {};
};

} // namespace Packets
} // namespace Network

#endif // INIT_HPP
