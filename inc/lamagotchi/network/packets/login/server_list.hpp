#ifndef SERVER_LIST_HPP
#define SERVER_LIST_HPP

#include "network/packets/packet.hpp"

#include <vector>

namespace Lamagotchi
{

namespace Network
{

namespace Packets
{

struct ServerList : Packet
{
    struct GameServer
    {
        GameServer(uint8_t id, uint32_t ip, uint32_t port) : id(id), ip(ip), port(port)
        {
        }

        uint8_t id = 0xFF;
        uint32_t ip = 0x00;
        uint32_t port = 0x00;
    };

    explicit ServerList(uint16_t length = 0x00, uint8_t type = 0x04) : Packet{length, type}
    {
    }

    uint8_t count = 0x00;
    std::vector<GameServer> servers;
};

} // namespace Packets
} // namespace Network
} // namespace Lamagotchi

#endif // SERVER_LIST_HPP
