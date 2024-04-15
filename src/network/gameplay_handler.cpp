#include "lamagotchi/network/gameplay_handler.h"

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

GameplayHandler::GameplayHandler()
{
}

PacketPtr GameplayHandler::deserialize(uint8_t* data)
{
}

DataPtr GameplayHandler::serialize(Packet& packet)
{
}

void GameplayHandler::init()
{
}

} // namespace Network
} // namespace Lamagotchi
