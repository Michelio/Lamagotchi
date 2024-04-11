#ifndef SCRAMBLE_HPP
#define SCRAMBLE_HPP

#include <stdint.h>
#include <utility>

namespace Crypting
{

static void scramble(uint8_t* const data)
{
    uint16_t i;

    for (i = 0; i < 4; ++i)
    {
        std::swap(data[0x00 + i], data[0x4d + i]);
    };

    // step 2 xor first 0x40 bytes with last 0x40 bytes
    for (i = 0; i < 0x40; ++i)
    {
        data[i] = data[i] ^ data[0x40 + i];
    };

    // step 3 xor bytes 0x0d - 0x10 with bytes 0x34 - 0x38
    for (i = 0; i < 4; ++i)
    {
        data[0x0d + i] = data[0x0d + i] ^ data[0x34 + i];
    };

    // step 4 xor last 0x40 bytes with first 0x40 bytes
    for (i = 0; i < 0x40; ++i)
    {
        data[0x40 + i] = data[0x40 + i] ^ data[i];
    };
}

static void unscramble(uint8_t* const data)
{
    uint16_t i;

    // step 1 xor last 0x40 bytes with first 0x40 bytes
    for (i = 0; i < 0x40; ++i)
    {
        data[0x40 + i] = data[0x40 + i] ^ data[i];
    };

    // step 2 xor bytes 0x0d - 0x10 with bytes 0x34 - 0x38
    for (i = 0; i < 4; ++i)
    {
        data[0x0d + i] = data[0x0d + i] ^ data[0x34 + i];
    };

    // step 3 xor first 0x40 bytes with last 0x40 bytes
    for (i = 0; i < 0x40; ++i)
    {
        data[i] = data[i] ^ data[0x40 + i];
    };

    for (i = 0; i < 4; ++i)
    {
        std::swap(data[0x00 + i], data[0x4d + i]);
    };
}

} // namespace Crypting

#endif // SCRAMBLE_HPP
