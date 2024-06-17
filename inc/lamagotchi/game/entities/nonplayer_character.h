#ifndef NONPLAYER_CHARACTER_H
#define NONPLAYER_CHARACTER_H

#include "live_entity.h"

namespace Game
{

class NonPlayerCharacter : public LiveEntity
{
public:
    NonPlayerCharacter() = default;
    explicit NonPlayerCharacter(const uint32_t objectId, std::wstring_view objectName, Vector3D position, bool isAlive);

    void setIsPet(bool isPet);
    bool getIsPet() const;
    void setIsAttackable(bool isAttackable);
    bool getIsAttackable() const;

protected:
    bool m_isPet = false;
    bool m_isAttackable = false;
};

} // namespace Game

#endif // NONPLAYER_CHARACTER_H
