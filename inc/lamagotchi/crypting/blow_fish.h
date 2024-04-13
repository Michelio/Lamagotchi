#ifndef BLOW_FISH_H
#define BLOW_FISH_H

#include <array>
#include <openssl/blowfish.h>
#include <stdint.h>

namespace Lamagotchi
{

namespace Crypting
{

static std::array<uint8_t, 0x10> s_blowFishKey = {0x6b, 0x60, 0xcb, 0x5b, 0x82, 0xce, 0x90, 0xb1,
                                                  0xcc, 0x2b, 0x6c, 0x55, 0x6c, 0x6c, 0x6c, 0x6c};

class BlowFish
{
public:
    explicit BlowFish(uint8_t* key, uint16_t length);
    void setKey(uint8_t* key, uint16_t length);

    void encrypt(uint8_t* data, uint16_t length);
    void decrypt(uint8_t* data, uint16_t length);

private:
    BF_KEY m_key;
};

} // namespace Crypting
} // namespace Lamagotchi

#endif // BLOW_FISH_H
