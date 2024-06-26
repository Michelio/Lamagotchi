#include "network/gameplay_handler.h"
#include "network/packet_handler.h"
#include "network/packets/game/char_info.hpp"
#include "network/packets/game/char_list.hpp"
#include "network/packets/game/char_selected.hpp"
#include "network/packets/game/crypt_init.hpp"
#include "network/packets/game/ex_info.hpp"
#include "network/packets/game/move_to_location.hpp"
#include "network/packets/game/net_ping.hpp"
#include "network/packets/game/npc_info.hpp"
#include "network/packets/game/protocol_version.hpp"
#include "network/packets/game/request_auth.hpp"
#include "network/packets/game/request_enter_world.hpp"
#include "network/packets/game/request_manor_list.hpp"
#include "network/packets/game/request_net_ping.hpp"
#include "network/packets/game/request_select_char.hpp"
#include "network/packets/game/status_update.hpp"
#include "network/packets/game/user_info.hpp"
#include "network/packets/packet.hpp"

#include <boost/endian.hpp>
#include <cstdint>
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
    // Interlude
    // if (packet->type == 0x00)
    if (packet->type == 0x2e)
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

    // User Info [32]
    m_parseHandler[0x32] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<UserInfo>(length, 0x32);

        std::memcpy(&packet->x, data + 3, sizeof(uint32_t));
        std::memcpy(&packet->y, data + 7, sizeof(uint32_t));
        std::memcpy(&packet->z, data + 11, sizeof(uint32_t));
        std::memcpy(&packet->objectId, data + 19, sizeof(uint32_t));

        uint16_t offset = 23;
        while (*std::bit_cast<uint16_t*>(&data[offset]) != 0x00)
        {
            packet->nickname += *std::bit_cast<uint16_t*>(&data[offset]);
            offset += 2;
        }
        offset += sizeof(uint16_t);
        offset += sizeof(uint32_t) * 3;
        std::memcpy(&packet->level, data + offset, sizeof(uint8_t));
        offset += sizeof(uint32_t);
        std::memcpy(&packet->experience, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->experience);
        offset += sizeof(uint32_t) * 4;
        std::memcpy(&packet->STR, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->STR);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->DEX, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->DEX);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->CON, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->CON);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->INT, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->INT);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->WIT, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->WIT);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->MEN, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->MEN);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->maximumHealthPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->maximumHealthPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->currentHealthPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->currentHealthPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->maximumManaPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->maximumManaPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->currentManaPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->currentManaPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->skillPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->skillPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->load, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->load);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->maximumLoad, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->maximumLoad);
        offset += sizeof(uint32_t) * 4 * 21 - 8;
        std::memcpy(&packet->pAttack, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->pAttack);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->attackSpeed, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->attackSpeed);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->pDefense, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->pDefense);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->evasion, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->evasion);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->accuracy, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->accuracy);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->critical, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->critical);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->mAttack, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->mAttack);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->castingSpeed, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->castingSpeed);
        offset += sizeof(uint32_t) * 2;
        std::memcpy(&packet->mDefense, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->mDefense);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->pvpStatus, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->pvpStatus);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->karma, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->karma);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->runningSpeed, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->runningSpeed);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->walkingSpeed, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->walkingSpeed);
        offset += sizeof(uint32_t);
        offset += sizeof(uint32_t) * 18;

        while (*std::bit_cast<uint16_t*>(&data[offset]) != 0x00)
        {
            uint16_t letter = *std::bit_cast<uint16_t*>(&data[offset]);
            boost::endian::little_to_native_inplace(letter);
            packet->title += letter;
            offset += 2;
        }
        offset += 2;

        offset += sizeof(uint32_t) * 5 + sizeof(uint16_t) + 1;
        std::memcpy(&packet->pkCount, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->pkCount);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->pvpCount, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->pvpCount);
        offset += sizeof(uint32_t);

        uint16_t cubicCount;
        std::memcpy(&cubicCount, data + offset, sizeof(uint16_t));
        boost::endian::little_to_native_inplace(cubicCount);
        offset += sizeof(uint16_t);
        offset += sizeof(uint16_t) * cubicCount;
        offset += sizeof(uint32_t) * 6 + sizeof(uint16_t) * 2;

        std::memcpy(&packet->maximumCombatPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->maximumCombatPoints);
        offset += sizeof(uint32_t);
        std::memcpy(&packet->currentCombatPoints, data + offset, sizeof(uint32_t));
        boost::endian::little_to_native_inplace(packet->currentCombatPoints);
        offset += sizeof(uint32_t);

        return packet;
    };

    // Char List [09]
    m_parseHandler[0x09] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharList>(length, 0x09);

        std::memcpy(&packet->count, data + 3, sizeof(uint32_t));

        return packet;
    };

    // Char Selected [0b]
    m_parseHandler[0x0b] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharSelected>(length, 0x0b);

        return packet;
    };

    // Status Update [0e]
    m_parseHandler[0x0e] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<StatusUpdate>(length);

        std::memcpy(&packet->objectId, data + 3, sizeof(uint32_t));
        std::memcpy(&packet->count, data + 7, sizeof(uint32_t));
        packet->newValues.reserve(packet->count);

        uint16_t offset = 7;
        for (int i = 0; i < packet->count; ++i)
        {
            uint32_t type;
            uint32_t value;

            offset += sizeof(uint32_t);
            std::memcpy(&type, data + offset, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            std::memcpy(&value, data + offset, sizeof(uint32_t));

            packet->newValues.emplace_back(type, value);
        }

        return packet;
    };

    // Request Game Start [12]
    m_parseHandler[0x12] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CharSelected>(length);
        std::cout << "0x12\n";

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

    // Crypt Init [2e]
    m_parseHandler[0x2e] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<CryptInit>(length, 0x2e);

        std::memcpy(packet->key.data(), data + 4, 0x10);

        return packet;
    };

    // Request Net Ping [d3]
    m_parseHandler[0xd3] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<RequestNetPing>(length);

        std::memcpy(&packet->id, data + 3, sizeof(uint32_t));

        return packet;
    };

    // Manor List [fe]
    m_parseHandler[0xfe] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<ExInfo>(length);

        packet->subType = data[3];

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

    // Request Enter World [11]
    m_buildHandler[0x11] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestEnterWorld*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;

        return data;
    };

    // Request Select Char [12]
    m_buildHandler[0x12] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestSelectChar*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, &obj->charNum, sizeof(uint32_t));

        return data;
    };

    // Request Auth Login [2b]
    m_buildHandler[0x2b] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<RequestAuth*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, obj->login.data(), obj->login.size());
        std::memcpy(data.get() + obj->login.size() + 5, obj->sessionKey.data(), 0x10);
        uint16_t offset = obj->login.size() + obj->sessionKey.size() + 5;
        data[offset] = 0x01;
        offset += 4;
        data[offset] = 0xc2;
        offset += 1;
        data[offset] = 0x02;

        return data;
    };

    // Net Ping [a8]
    m_buildHandler[0xa8] = [](Packet& packet) -> DataPtr {
        boost::endian::native_to_little_inplace(packet.length);

        auto obj = std::bit_cast<NetPing*>(&packet);

        DataPtr data(new uint8_t[obj->length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, &obj->id, sizeof(uint32_t));

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
        data[3] = 0x01;

        return data;
    };
}

} // namespace Network
} // namespace Lamagotchi
