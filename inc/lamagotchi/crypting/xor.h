#ifndef XOR_H
#define XOR_H

#include <array>
#include <stdint.h>

namespace Lamagotchi
{

namespace Crypting
{

class Xor
{
public:
    explicit Xor(std::array<uint8_t, 0x10> key);
    void encrypt(uint8_t* data, uint16_t length);
    void decrypt(uint8_t* data, uint16_t length);

private:
    std::array<uint8_t, 0x10> m_encryptKey = {};
    std::array<uint8_t, 0x10> m_decryptKey = {};
};

} // namespace Crypting
} // namespace Lamagotchi

#endif // XOR_H
