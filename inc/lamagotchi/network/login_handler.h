#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "crypting/blow_fish.h"
#include "crypting/rsa.h"
#include "network/packet_handler.h"

#include <functional>
#include <optional>

namespace Lamagotchi
{

namespace Network
{

class LoginHandler : public PacketHandler
{
public:
    LoginHandler();
    [[nodiscard]] std::array<uint8_t, 0x08> getSessionKey() const;

    [[nodiscard]] PacketPtr deserialize(uint8_t* data) override final;
    [[nodiscard]] DataPtr serialize(Packets::Packet& packet) override final;
    static void init();

private:
    static std::array<std::function<PacketPtr(uint8_t* data, uint16_t length)>, 0xff> m_parseHandler;
    static std::array<std::function<DataPtr(Packets::Packet& packet)>, 0xff> m_buildHandler;
    Crypting::BlowFish m_blowFish;
    std::optional<Crypting::Rsa> m_rsa;
    std::array<uint8_t, 0x08> m_sessionKey1 = {};
};

} // namespace Network
} // namespace Lamagotchi

#endif // LOGIN_HANDLER_H
