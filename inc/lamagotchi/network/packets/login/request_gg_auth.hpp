#ifndef REQUEST_GG_AUTH_H
#define REQUEST_GG_AUTH_H

#include "lamagotchi/network/packets/packet.hpp"

namespace Network
{

namespace Packets
{

struct RequestGGAuthProperties
{
    RequestGGAuthProperties& sessionKey(uint32_t key)
    {
        m_key = key;
        return *this;
    }

    RequestGGAuthProperties& length(uint16_t length)
    {
        m_length = length;
        return *this;
    }

    RequestGGAuthProperties& type(uint8_t type)
    {
        m_type = type;
        return *this;
    }

    uint32_t m_key = 0x00;
    uint16_t m_length = 0x2a;
    uint8_t m_type = 0x07;
};

struct RequestGGAuth : Packet
{
    RequestGGAuth(RequestGGAuthProperties& properties)
        : Packet(properties.m_length, properties.m_type), sessionKey(properties.m_key)
    {
    }

    uint32_t sessionKey;
};

} // namespace Packets
} // namespace Network

#endif // REQUEST_GG_AUTH_H
