#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "lamagotchi/crypting/blow_fish.h"
#include "lamagotchi/network/packet_handler.h"

#include <functional>

namespace Network
{

class LoginHandler : public PacketHandler
{
public:
    LoginHandler();
    [[nodiscard]] packetPointer parse(uint8_t* data) override final;
    [[nodiscard]] dataPointer build(Packets::Packet& packet) override final;

private:
    static std::array<std::function<packetPointer(uint8_t* data, uint16_t length)>, 0xff> m_parseHandler;
    static std::array<std::function<dataPointer(Packets::Packet& packet)>, 0xff> m_buildHandler;
    Crypting::BlowFish m_blowFish;
};

} // namespace Network

#endif // LOGIN_HANDLER_H
