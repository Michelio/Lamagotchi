#ifndef PET_H
#define PET_H

#include "game/entities/entity.h"
#include "nonplayer_character.h"

#include <cstdint>
#include <string_view>

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

#endif // PET_H
