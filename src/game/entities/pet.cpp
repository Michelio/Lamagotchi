#include "game/entities/pet.h"

namespace Lamagotchi
{

namespace Game
{

Pet::Pet(const uint32_t objectId, std::wstring_view objectName, const Vector3D position, bool isAlive = false)
    : NonPlayerCharacter{objectId, objectName, position, isAlive}
{
}

void Pet::setFed(const uint32_t fed)
{
    m_fed = fed;
}

uint32_t Pet::getFed() const
{
    return m_fed;
}

void Pet::setPetType(const PetType petType)
{
    m_petType = petType;
}

PetType Pet::getPetType() const
{
    return m_petType;
}

} // namespace Game
} // namespace Lamagotchi
