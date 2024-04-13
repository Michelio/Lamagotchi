#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "lamagotchi/crypting/blow_fish.h"
#include "lamagotchi/crypting/rsa.h"
#include "lamagotchi/network/packet_handler.h"

#include <functional>
#include <optional>

namespace Network
{

class LoginHandler : public PacketHandler
{
public:
    LoginHandler();
    void setKey(std::array<uint8_t, 0x10> key);

    [[nodiscard]] packetPointer deserialize(uint8_t* data) override final;
    [[nodiscard]] dataPointer serialize(Packets::Packet& packet) override final;
    static void init();

private:
    static std::array<std::function<packetPointer(uint8_t* data, uint16_t length)>, 0xff> m_parseHandler;
    static std::array<std::function<dataPointer(Packets::Packet& packet)>, 0xff> m_buildHandler;
    Crypting::BlowFish m_blowFish;
    std::optional<Crypting::Rsa> m_rsa;
    std::array<uint8_t, 0x08> m_sessionKey1 = {};
    std::array<uint8_t, 0x08> m_sessionKey2 = {};
};

} // namespace Network

#endif // LOGIN_HANDLER_H
