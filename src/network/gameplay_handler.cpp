#include "lamagotchi/network/gameplay_handler.h"
#include "lamagotchi/network/packets/game/char_info.hpp"
#include "lamagotchi/network/packets/game/char_list.hpp"
#include "lamagotchi/network/packets/game/char_selected.hpp"
#include "lamagotchi/network/packets/game/crypt_init.hpp"
#include "lamagotchi/network/packets/game/manor_list.hpp"
#include "lamagotchi/network/packets/game/move_to_location.hpp"
#include "lamagotchi/network/packets/game/npc_info.hpp"
#include "lamagotchi/network/packets/game/protocol_version.hpp"
#include "lamagotchi/network/packets/game/request_auth.hpp"
#include "lamagotchi/network/packets/game/request_enter_world.hpp"
#include "lamagotchi/network/packets/game/request_manor_list.hpp"
#include "lamagotchi/network/packets/game/request_select_char.hpp"
#include "lamagotchi/network/packets/packet.hpp"

#include <boost/endian.hpp>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace Lamagotchi
{

namespace Network
{

using namespace Packets;

std::array<std::function<PacketPtr(uint8_t* data, uint16_t length)>, 0xff> GameplayHandler::m_parseHandler;
std::array<std::function<DataPtr(Packets::Packet& packet)>, 0xff> GameplayHandler::m_buildHandler;

PacketPtr GameplayHandler::deserialize(uint8_t* data)
{
    uint16_t length = 0;
    uint8_t type = 0xff;

    length = *std::bit_cast<uint16_t*>(data);
    boost::endian::little_to_native_inplace(length);

    if (m_xor) [[likely]]
    {
        m_xor->decrypt(data + 2, length - 2);
    }

    type = data[2];
    printPacket(data, length);

    if (!m_parseHandler[type])
    {
        std::cerr << std::setfill('0');
        std::cerr << "Unable to deserialize " << std::hex << std::setw(2) << static_cast<uint32_t>(type) << ".\n";
        return std::make_shared<Packet>();
    }

    auto packet = m_parseHandler[type](data, length);

    if (packet->type == 0x00)
    {
        m_xor.emplace(std::bit_cast<CryptInit*>(packet.get())->key);
    }

    return packet;
}

DataPtr GameplayHandler::serialize(Packet& packet)
{
    if (!m_buildHandler[packet.type]) [[unlikely]]
    {
        std::cerr << std::setfill('0');
        std::cerr << "Unable to serialize " << std::hex << std::setw(2) << static_cast<uint32_t>(packet.type) << ".\n";
        return nullptr;
    }

    auto data = m_buildHandler[packet.type](packet);

    printPacket(data.get(), packet.length);

    if (m_xor) [[likely]]
    {
        m_xor->encrypt(data.get() + 2, packet.length - 2);
    }

    return data;
}

void GameplayHandler::init()
{
    // Server side packets
    //
    // Crypt Init [00]
    m_parseHandler[0x00] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CryptInit>(length);

        std::memcpy(packet->key.data(), data + 4, 0x10);

        return packet;
    };

    // Move To Location [01]
    m_parseHandler[0x01] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<MoveToLocation>(length);

        std::memcpy(&packet->objectId, data + 3, sizeof(uint32_t));
        std::memcpy(&packet->destX, data + 7, sizeof(uint32_t));
        std::memcpy(&packet->destY, data + 11, sizeof(uint32_t));
        std::memcpy(&packet->destZ, data + 15, sizeof(uint32_t));
        std::memcpy(&packet->sourceX, data + 19, sizeof(uint32_t));
        std::memcpy(&packet->sourceY, data + 23, sizeof(uint32_t));
        std::memcpy(&packet->sourceZ, data + 27, sizeof(uint32_t));

        return packet;
    };

    // Char Info [03]
    m_parseHandler[0x03] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharInfo>(length);

        std::memcpy(&packet->x, data + 3, sizeof(uint32_t));
        std::memcpy(&packet->y, data + 7, sizeof(uint32_t));
        std::memcpy(&packet->z, data + 11, sizeof(uint32_t));
        std::memcpy(&packet->objectId, data + 19, sizeof(uint32_t));

        return packet;
    };

    // Char List [13]
    m_parseHandler[0x13] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharList>(length);

        std::memcpy(&packet->count, data + 3, sizeof(uint32_t));

        return packet;
    };

    // Char Selected [15]
    m_parseHandler[0x15] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharSelected>(length);

        return packet;
    };

    // Npc Info [16]
    m_parseHandler[0x16] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<NpcInfo>(length);

        std::memcpy(&packet->objectId, data + 3, sizeof(uint32_t));
        std::memcpy(&packet->npcTypeid, data + 7, sizeof(uint32_t));
        std::memcpy(&packet->isAttackable, data + 11, sizeof(uint32_t));
        std::memcpy(&packet->x, data + 15, sizeof(uint32_t));
        std::memcpy(&packet->y, data + 19, sizeof(uint32_t));
        std::memcpy(&packet->z, data + 23, sizeof(uint32_t));

        return packet;
    };

    // Manor List [fe]
    m_parseHandler[0xfe] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<ManorList>(length);

        return packet;
    };

    // Client side packets
    //
    // Protocol Version [00]
    m_buildHandler[0x00] = [](Packet& packet) -> DataPtr {
        packet.length = 0x010b;
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<ProtocolVersion*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), obj->data.data(), obj->length);

        return data;
    };

    // Request Enter World [03]
    m_buildHandler[0x03] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestEnterWorld*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;

        return data;
    };

    // Request Auth [08]
    m_buildHandler[0x08] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestAuth*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, obj->login.data(), obj->login.size());
        std::memcpy(data.get() + obj->login.size() + 5, obj->sessionKey.data(), 0x10);
        uint16_t offset = obj->login.size() + 5 + 0x10;
        data[offset] = 0x01;

        return data;
    };

    // Request Select Char [0d]
    m_buildHandler[0x0d] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestSelectChar*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, &obj->charNum, sizeof(uint32_t));

        return data;
    };

    // Request Manor List [d0]
    m_buildHandler[0xd0] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestManorList*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        data[3] = 0x08;

        return data;
    };
}

} // namespace Network
} // namespace Lamagotchi
