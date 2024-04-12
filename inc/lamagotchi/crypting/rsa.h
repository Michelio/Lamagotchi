#ifndef RSA_H
#define RSA_H

#include <array>
#include <openssl/rsa.h>

namespace Crypting
{

class Rsa
{
public:
    explicit Rsa(std::array<uint8_t, 0x80> key);
    ~Rsa();
    void encrypt(uint8_t* data, uint16_t length);
    void decrypt(uint8_t* data, uint16_t length);

private:
    RSA* m_key = nullptr;
    BIGNUM* m_n = nullptr;
    BIGNUM* m_e = nullptr;
};

} // namespace Crypting

#endif // RSA_H
