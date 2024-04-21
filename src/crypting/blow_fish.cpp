#include "crypting/blow_fish.h"

#include <bit>

namespace Lamagotchi
{

namespace Crypting
{

BlowFish::BlowFish(uint8_t* key, uint16_t length)
{
    BF_set_key(&m_key, length, key);
}

void BlowFish::setKey(uint8_t* key, uint16_t length)
{
    BF_set_key(&m_key, length, key);
}

void BlowFish::encrypt(uint8_t* data, uint16_t length)
{
    for (int i = 2; i < length; i += 8)
    {
        BF_encrypt(std::bit_cast<BF_LONG*>(&data[i]), &m_key);
    }
}

void BlowFish::decrypt(uint8_t* data, uint16_t length)
{
    for (int i = 2; i < length; i += 8)
    {
        BF_decrypt(std::bit_cast<BF_LONG*>(&data[i]), &m_key);
    }
}

} // namespace Crypting
} // namespace Lamagotchi
