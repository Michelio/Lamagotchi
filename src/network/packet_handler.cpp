#include "lamagotchi/network/packet_handler.h"

#include <bit>
#include <iomanip>
#include <iostream>

namespace Lamagotchi
{

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

void PacketHandler::printPacket(const uint8_t* data, uint16_t length)
{
    std::cout << std::hex << std::setfill('0');
    for (int i = 0; i < length; ++i)
    {
        if (i % 0x10 == 0)
        {
            std::cout << "\n0x" << std::setw(2) << static_cast<uint32_t>(i) << " | ";
        }

        std::cout << std::setw(2) << static_cast<uint32_t>(data[i]);

        if (i != 0 && (i + 1) % 4 == 0)
            std::cout << '\t';

        else
            std::cout << ' ';
    }
    std::cout << '\n';
}

} // namespace Network
} // namespace Lamagotchi
