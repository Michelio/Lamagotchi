#include "game/entities/nonplayer_character.h"
#include "game/entities/entity.h"
#include "game/entities/live_entity.h"
#include <cstdint>
#include <string_view>

namespace Game
{

NonPlayerCharacter::NonPlayerCharacter(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                                       bool isAlive)
    : LiveEntity{objectId, objectName, position, isAlive}
{
}

} // namespace Game
