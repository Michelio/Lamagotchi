#ifndef GAMEPLAY_HANDLER
#define GAMEPLAY_HANDLER

#include "lamagotchi/network/packet_handler.h"

#include "lamagotchi/crypting/xor.h"
#include <array>
#include <functional>
#include <optional>

namespace Lamagotchi
{

namespace Network
{

class GameplayHandler : public PacketHandler
{
public:
    GameplayHandler() = default;

    [[nodiscard]] PacketPtr deserialize(uint8_t* data) override final;
    [[nodiscard]] DataPtr serialize(Packets::Packet& packet) override final;
    static void init();

private:
    static std::array<std::function<PacketPtr(uint8_t* data, uint16_t length)>, 0xff> m_parseHandler;
    static std::array<std::function<DataPtr(Packets::Packet& packet)>, 0xff> m_buildHandler;
    std::optional<Crypting::Xor> m_xor;
};

} // namespace Network
} // namespace Lamagotchi

#endif // GAMEPLAY_HANDLER
