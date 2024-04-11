#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/network/packets/login/init.hpp"
#include "lamagotchi/network/packets/login/request_gg_auth.hpp"

namespace Network
{

using namespace Packets;

std::array<std::function<packetPointer(uint8_t*, uint16_t)>, 0xff> LoginHandler::m_parseHandler = {
    // Init [00]
    [](uint8_t* data, uint16_t length) -> packetPointer { return std::make_shared<Init>(data, length); },
};

std::array<std::function<dataPointer(Packet&)>, 0xff> LoginHandler::m_buildHandler = {
    // RequestGGAuth [07]
    [](Packet& packet) -> dataPointer {
        auto obj = *std::bit_cast<RequestGGAuth*>(&packet);
        std::shared_ptr<uint8_t[]> data(new uint8_t[packet.length]);

        uint16_t offset = 0;
        std::memcpy(data.get(), &obj.length, sizeof(uint16_t));
        offset += sizeof(uint16_t);
        data.get()[offset] = obj.type;
        offset += sizeof(uint8_t);
        std::memcpy(data.get() + offset, &obj.sessionKey, sizeof(uint32_t));
        offset += sizeof(uint32_t);
        uint32_t sum = calculateChecksum(data.get(), obj.length);
        offset += sizeof(uint32_t) * 5 + sizeof(uint16_t);
        std::memcpy(data.get() + offset, &sum, sizeof(uint32_t));

        return data;
    },
};

LoginHandler::LoginHandler() : m_blowFish(Crypting::s_blowFishKey.data(), Crypting::s_blowFishKey.size())
{
}

void LoginHandler::setKey(std::array<uint8_t, 0x10> key)
{
    m_blowFish.setKey(key.data(), key.size());
}

packetPointer LoginHandler::deserialize(uint8_t* data)
{
    uint16_t length = 0;
    uint8_t type = 0xff;
    uint16_t offset = 0;

    length = *std::bit_cast<uint16_t*>(data);
    offset = sizeof(uint16_t);
    m_blowFish.decrypt(data, length);
    type = data[offset];

    return m_parseHandler[type](data, length);
}

dataPointer LoginHandler::serialize(Packet& packet)
{
    auto data = m_buildHandler[packet.type](packet);
    m_blowFish.encrypt(data.get(), packet.length);
    return data;
}

} // namespace Network
