#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <memory>
#include <stdint.h>

namespace Network
{

namespace Packets
{
class Packet;
}

class PacketHandler
{
public:
    using dataPointer = std::shared_ptr<uint8_t>;
    using packetPointer = std::shared_ptr<Packets::Packet>;

    [[nodiscard]] uint32_t calculateChecksum(uint8_t* data, uint16_t length);
    [[nodiscard]] virtual packetPointer parse(uint8_t* data) = 0;
    [[nodiscard]] virtual dataPointer build(Packets::Packet& packet) = 0;
    virtual ~PacketHandler() = default;
};

} // namespace Network

#endif // PACKET_HANDLER_H
