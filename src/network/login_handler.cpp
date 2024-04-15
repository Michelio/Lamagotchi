#include "lamagotchi/network/login_handler.h"
#include "lamagotchi/crypting/scramble.hpp"
#include "lamagotchi/network/packets/login/gameguard_auth.hpp"
#include "lamagotchi/network/packets/login/init.hpp"
#include "lamagotchi/network/packets/login/login_fail.hpp"
#include "lamagotchi/network/packets/login/login_ok.hpp"
#include "lamagotchi/network/packets/login/play_fail.hpp"
#include "lamagotchi/network/packets/login/play_ok.hpp"
#include "lamagotchi/network/packets/login/request_gg_auth.hpp"
#include "lamagotchi/network/packets/login/request_login_auth.hpp"
#include "lamagotchi/network/packets/login/request_server_list.hpp"
#include "lamagotchi/network/packets/login/request_server_login.hpp"
#include "lamagotchi/network/packets/login/server_list.hpp"

#include <boost/endian.hpp>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace Lamagotchi
{

namespace Network
{

using namespace Packets;

std::array<std::function<PacketPtr(uint8_t* data, uint16_t length)>, 0xff> LoginHandler::m_parseHandler;
std::array<std::function<DataPtr(Packets::Packet& packet)>, 0xff> LoginHandler::m_buildHandler;

LoginHandler::LoginHandler() : m_blowFish(Crypting::s_blowFishKey.data(), Crypting::s_blowFishKey.size())
{
}

std::array<uint8_t, 0x08> LoginHandler::getSessionKey() const
{
    return m_sessionKey1;
}

PacketPtr LoginHandler::deserialize(uint8_t* data)
{
    uint16_t length = 0;
    uint8_t type = 0xff;
    uint16_t offset = 0;

    length = *std::bit_cast<uint16_t*>(data);
    boost::endian::little_to_native_inplace(length);
    m_blowFish.decrypt(data, length);
    type = data[2];
    printPacket(data, length);

    if (!m_parseHandler[type])
    {
        std::cerr << std::setfill('0');
        std::cerr << "Unable to deserialize " << std::hex << std::setw(2) << static_cast<uint32_t>(type) << ".\n";
        return nullptr;
    }

    auto packet = m_parseHandler[type](data, length);
    if (packet->type == 0x00)
    {
        Crypting::unscramble(std::bit_cast<Init*>(packet.get())->rsaKey.data());
        m_rsa.emplace(std::bit_cast<Init*>(packet.get())->rsaKey);
        m_blowFish.setKey(std::bit_cast<Init*>(packet.get())->bfKey.data(), 0x10);
    }

    return packet;
}

DataPtr LoginHandler::serialize(Packet& packet)
{
    if (!m_buildHandler[packet.type])
    {
        std::cerr << std::setfill('0');
        std::cerr << "Unable to serialize " << std::hex << std::setw(2) << static_cast<uint32_t>(packet.type) << ".\n";
        return nullptr;
    }

    auto data = m_buildHandler[packet.type](packet);

    if (packet.type == 0x00)
    {
        m_rsa->encrypt(data.get(), 0x80);
        auto sum = calculateChecksum(data.get(), packet.length);
        boost::endian::native_to_little_inplace(sum);
        std::memcpy(data.get() + packet.length - 16, &sum, sizeof(sum));
    }

    else if (packet.type == 0x02)
    {
        std::memcpy(data.get() + 3, m_sessionKey1.data(), 0x08);
        auto sum = calculateChecksum(data.get(), packet.length);
        boost::endian::native_to_little_inplace(sum);
        std::memcpy(data.get() + 18, &sum, sizeof(uint32_t));
    }

    else if (packet.type == 0x05)
    {
        std::memcpy(m_sessionKey1.data(), data.get() + 3, 0x08);
        auto sum = calculateChecksum(data.get(), packet.length);
        boost::endian::native_to_little_inplace(sum);
        std::memcpy(data.get() + 18, &sum, sizeof(uint32_t));
    }
    printPacket(data.get(), packet.length);

    m_blowFish.encrypt(data.get(), packet.length);

    return data;
}

void LoginHandler::init()
{
    // Server side packets
    //
    // Init [00]
    m_parseHandler[0x00] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        uint16_t i = length - 8;
        uint32_t k = *std::bit_cast<uint32_t*>(data + length - 8);

        while (i >= 6 && i < length)
        {
            *std::bit_cast<uint32_t*>(&data[i]) = *std::bit_cast<uint32_t*>(&data[i]) ^ k;
            k -= *std::bit_cast<uint32_t*>(&data[i]);
            i -= 4;
        }

        auto packet = std::make_shared<Init>(length, data[2]);

        std::memcpy(&packet->sessionId, data + 3, sizeof(uint32_t));
        std::memcpy(packet->rsaKey.data(), data + 11, 0x80);
        std::memcpy(packet->bfKey.data(), data + length - 31, 0x10);
        return packet;
    };

    // Login Fail [01]
    m_parseHandler[0x01] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<LoginFail>(length, data[2]);

        packet->reason = data[3];

        return packet;
    };

    // Login Ok [03]
    m_parseHandler[0x03] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<LoginOk>(length, data[2]);

        std::memcpy(packet->sessionKey.data(), data + 3, 0x08);

        return packet;
    };

    // Server List [04]
    m_parseHandler[0x04] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<ServerList>(length, data[2]);

        packet->count = data[3];

        uint8_t i = packet->count;
        uint16_t offset = 5;
        while (i)
        {
            uint8_t id = data[offset];
            offset += 1;
            uint32_t ip = 0x00;
            std::memcpy(&ip, data + offset, sizeof(uint32_t));
            boost::endian::little_to_native_inplace(ip);
            offset += 4;
            uint32_t port = 0x00;
            std::memcpy(&port, data + offset, sizeof(uint32_t));
            boost::endian::little_to_native_inplace(port);
            offset += 11;

            packet->servers.emplace_back(id, ip, port);
            --i;
        }

        return packet;
    };

    // Play Fail [06]
    m_parseHandler[0x06] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<PlayFail>(length, data[2]);

        packet->reason = data[3];
        std::memcpy(&packet->reason, data + 3, sizeof(uint32_t));

        return packet;
    };

    // Play Ok [07]
    m_parseHandler[0x07] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<PlayOk>(length, data[2]);

        std::memcpy(packet->sessionKey.data(), data + 3, 0x08);

        return packet;
    };

    // Gameguard Auth [0b]
    m_parseHandler[0x0b] = [](uint8_t* data, uint16_t length) -> PacketPtr {
        auto packet = std::make_shared<GameguardAuth>(length, data[2]);

        std::memcpy(&packet->ggKey, data + 3, sizeof(uint32_t));

        return packet;
    };

    // Client side packets
    //
    // Request Login Auth [00]
    m_buildHandler[0x00] = [](Packet& packet) -> DataPtr {
        packet.length = 0xb2;
        boost::endian::native_to_little_inplace(packet.length);
        auto obj = std::bit_cast<RequestLoginAuth*>(&packet);

        DataPtr data(new uint8_t[packet.length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        uint16_t offset = 0;
        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        data[94] = 0x20;
        std::memcpy(data.get() + 97, obj->login.data(), obj->login.length());
        std::memcpy(data.get() + 111, obj->password.data(), obj->password.length());
        std::memcpy(data.get() + 131, &obj->ggKey, sizeof(uint32_t));
        data[151] = 0x08;

        return data;
    };

    // Request Server Login [02]
    m_buildHandler[0x02] = [](Packet& packet) -> DataPtr {
        packet.length = 0x22;
        boost::endian::native_to_little_inplace(packet.length);
        auto obj = std::bit_cast<RequestServerLogin*>(&packet);
        DataPtr data(new uint8_t[packet.length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        data[11] = obj->serverId;

        return data;
    };

    // Request Server List [05]
    m_buildHandler[0x05] = [](Packet& packet) -> DataPtr {
        packet.length = 0x22;
        boost::endian::native_to_little_inplace(packet.length);
        auto obj = std::bit_cast<RequestServerList*>(&packet);
        DataPtr data(new uint8_t[packet.length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, obj->sessionKey.data(), 0x08);

        return data;
    };

    // Request Gameguard Auth [07]
    m_buildHandler[0x07] = [](Packet& packet) -> DataPtr {
        packet.length = 0x2a;
        boost::endian::native_to_little_inplace(packet.length);
        auto obj = std::bit_cast<RequestGGAuth*>(&packet);
        DataPtr data(new uint8_t[packet.length]);
        std::fill(data.get(), data.get() + packet.length, 0x00);

        std::memcpy(data.get(), &obj->length, sizeof(uint16_t));
        data[2] = obj->type;
        std::memcpy(data.get() + 3, &obj->sessionId, sizeof(uint32_t));
        uint32_t sum = calculateChecksum(data.get(), obj->length);
        std::memcpy(data.get() + 26, &sum, sizeof(uint32_t));

        return data;
    };
}

} // namespace Network
} // namespace Lamagotchi
