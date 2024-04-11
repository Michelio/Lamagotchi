#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/login/init.hpp"

#include <cstring>

namespace Network
{

using namespace Packets;

std::array<std::function<LoginHandler::packetPointer(uint8_t*, uint16_t)>, 0xff> LoginHandler::m_parseHandler = {
    // Init [00]
    [](uint8_t* data, uint16_t length) -> LoginHandler::packetPointer {
        auto packet = std::make_shared<Init>();
        uint16_t i = length - 8;
        uint32_t k = *std::bit_cast<uint32_t*>(data + length - 8);

        while (i >= 6 && i < length)
        {
            *std::bit_cast<uint32_t*>(&data[i]) = *std::bit_cast<uint32_t*>(&data[i]) ^ k;
            k -= *std::bit_cast<uint32_t*>(&data[i]);
            i -= 4;
        }

        uint16_t offset = sizeof(uint16_t) + sizeof(uint8_t);
        std::memcpy(&packet->session_key, data + offset, sizeof(uint32_t));
        offset += sizeof(uint32_t) * 2;
        std::memcpy(packet->rsa_key.data(), data + offset, 0x80);
        offset += 0x80 + sizeof(uint32_t) * 4;
        std::memcpy(packet->bf_key.data(), data + offset, 0x10);

        return std::static_pointer_cast<Packet>(packet);
    },
};
LoginHandler::LoginHandler() : m_blowFish(Crypting::s_blowFishKey.data(), Crypting::s_blowFishKey.size())
{
}

LoginHandler::packetPointer LoginHandler::parse(uint8_t* data)
{
    uint16_t length = 0;
    uint8_t type = 0xff;
    uint16_t offset = 0;

    length = *std::bit_cast<uint16_t*>(data);
    offset = sizeof(length);
    m_blowFish.decrypt(data, length);
    type = data[offset];
    auto packet = m_parseHandler[type](data, length);

    m_blowFish.setKey(std::static_pointer_cast<Init>(packet)->bf_key.data(), 0x10);

    return packet;
}

LoginHandler::dataPointer LoginHandler::build(Packet& packet)
{
    std::shared_ptr<uint8_t> data;
    return data;
}

} // namespace Network
