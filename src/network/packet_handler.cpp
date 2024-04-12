#include "lamagotchi/network/packet_handler.h"

#include <bit>

namespace Network
{

uint32_t PacketHandler::calculateChecksum(uint8_t* data, uint16_t length)
{
    uint32_t sum = 0;

    for (uint16_t i = 2; i < length; i += 4)
    {
        sum ^= *std::bit_cast<uint32_t*>(&data[i]);
    }

    return sum;
}

} // namespace Network
