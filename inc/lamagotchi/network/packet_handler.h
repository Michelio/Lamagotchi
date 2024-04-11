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

using dataPointer = std::shared_ptr<uint8_t[]>;
using packetPointer = std::shared_ptr<Packets::Packet>;

class PacketHandler
{
public:
    [[nodiscard]] static uint32_t calculateChecksum(uint8_t* data, uint16_t length);
    [[nodiscard]] virtual packetPointer deserialize(uint8_t* data) = 0;
    [[nodiscard]] virtual dataPointer serialize(Packets::Packet& packet) = 0;
    virtual ~PacketHandler() = default;
};

} // namespace Network

#endif // PACKET_HANDLER_H
