#include "lamagotchi/crypting/rsa.h"

#include <iostream>

namespace Crypting
{

Rsa::Rsa(std::array<uint8_t, 0x80> key) : m_key(RSA_new())
{
    m_n = BN_bin2bn(key.data(), 128, nullptr);
    m_e = BN_new();
    BN_set_word(m_e, 65537);
    RSA_set0_key(m_key.get(), m_n, m_e, nullptr);
}

void Rsa::encrypt(uint8_t* data, uint16_t length)
{
    int result = RSA_public_encrypt(length, data + 3, data + 3, m_key.get(), RSA_NO_PADDING);

    if (result < 0)
    {
        std::cerr << "RSA encryption has failed.\n";
        // TODO: handle an error.
    }
}

void Rsa::decrypt(uint8_t* data, uint16_t length)
{
    int result = RSA_public_decrypt(length, data + 3, data + 3, m_key.get(), RSA_NO_PADDING);

    if (result < 0)
    {
        std::cerr << "RSA decryption has failed.\n";
        // TODO: handle an error.
    }
}

} // namespace Crypting
