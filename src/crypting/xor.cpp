#include "crypting/xor.h"

namespace Lamagotchi
{

namespace Crypting
{

Xor::Xor(std::array<uint8_t, 0x10> key) : m_encryptKey(key), m_decryptKey(key)
{
}

void Xor::encrypt(uint8_t* data, uint16_t length)
{
    int temp = 0;

    for (uint16_t i = 0; i < length; ++i)
    {
        int temp2 = data[i] & 0xff;
        data[i] = (temp2 ^ (m_encryptKey[i & 15] & 0xff) ^ temp);
        temp = data[i];
    };

    int old = m_encryptKey[8] & 0xff;
    old |= (m_encryptKey[9] << 0x08) & 0xff00;
    old |= (m_encryptKey[10] << 0x10) & 0xff0000;
    old |= (m_encryptKey[11] << 0x18) & 0xff000000;

    old += length;

    m_encryptKey[8] = old & 0xff;
    m_encryptKey[9] = (old >> 0x08) & 0xff;
    m_encryptKey[10] = (old >> 0x10) & 0xff;
    m_encryptKey[11] = (old >> 0x18) & 0xff;
}

void Xor::decrypt(uint8_t* data, uint16_t length)
{
    int temp = 0;

    for (uint16_t i = 0; i < length; ++i)
    {
        int temp2 = data[i] & 0xff;
        data[i] = (temp2 ^ (m_decryptKey[i & 15] & 0xff) ^ temp);
        temp = temp2;
    };

    int old = m_decryptKey[8] & 0xff;
    old |= (m_decryptKey[9] << 0x08) & 0xff00;
    old |= (m_decryptKey[10] << 0x10) & 0xff0000;
    old |= (m_decryptKey[11] << 0x18) & 0xff000000;

    old += length;

    m_decryptKey[8] = old & 0xff;
    m_decryptKey[9] = (old >> 0x08) & 0xff;
    m_decryptKey[10] = (old >> 0x10) & 0xff;
    m_decryptKey[11] = (old >> 0x18) & 0xff;
}

} // namespace Crypting
} // namespace Lamagotchi
