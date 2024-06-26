#ifndef PET_H
#define PET_H

#include "nonplayer_character.h"

namespace Lamagotchi
{

namespace Game
{

enum class PetType
{
    UNKNOWN,
    SUMMON,
    PET
};

class Pet : public NonPlayerCharacter
{
public:
    Pet() = default;
    explicit Pet(const uint32_t objectId, std::wstring_view objectName, const Vector3D position, bool isAlive);

    void setFed(const uint32_t fed);
    uint32_t getFed() const;
    void setPetType(const PetType petType);
    PetType getPetType() const;

private:
    uint32_t m_fed = 0;
    PetType m_petType = PetType::UNKNOWN;
};

} // namespace Game
} // namespace Lamagotchi

#endif // PET_H
