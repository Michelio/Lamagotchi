#ifndef STATUS_UPDATE_HPP
#define STATUS_UPDATE_HPP

#include "network/packets/packet.hpp"

#include <utility>
#include <vector>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct StatusUpdate : Packet
{
    explicit StatusUpdate(uint16_t length, uint8_t type = 0x0e) : Packet{length, type}
    {
    }

    uint32_t objectId = 0x00;
    uint32_t count = 0x00;
    std::vector<std::pair<uint32_t, uint32_t>> newValues;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // STATUS_UPDATE_HPP
