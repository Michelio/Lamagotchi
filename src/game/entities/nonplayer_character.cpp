#include "game/entities/nonplayer_character.h"

namespace Lamagotchi
{

namespace Game
{

NonPlayerCharacter::NonPlayerCharacter(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                                       bool isAlive)
    : LiveEntity{objectId, objectName, position, isAlive}
{
}

} // namespace Game
} // namespace Lamagotchi
