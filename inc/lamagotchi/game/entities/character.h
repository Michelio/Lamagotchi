#ifndef CHARACTER_H
#define CHARACTER_H

#include "live_entity.h"

namespace Game
{

class Character : public LiveEntity
{
public:
    Character() = default;
    explicit Character(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                       const bool isAlive);

    void setCurrentCombatPoints(const uint32_t currentCombatPoints);
    uint32_t getCurrentCombatPoints() const;
    void setMaximumCombatPoints(const uint32_t maximumCombatPoints);
    uint32_t getMaximumCombatPoints() const;
    void setClassId(const uint32_t classId);
    uint32_t getClassId() const;
    void setMainClassId(const uint32_t mainClassId);
    uint32_t getMainClassId() const;
    void setRace(const uint32_t race);
    uint32_t getRace() const;
    void setSex(const uint32_t sex);
    uint32_t getSex() const;
    void setHero(const uint32_t hero);
    uint32_t getHero() const;
    void setNoble(const uint32_t noble);
    uint32_t getNoble() const;

protected:
    uint32_t m_classId = 0;
    uint32_t m_mainClassId = 0;
    uint32_t m_currentCombatPoints = 0;
    uint32_t m_maximumCombatPoints = 0;
    uint8_t m_race = 0;
    uint8_t m_sex = 0;
    uint8_t m_hero = 0;
    uint8_t m_noble = 0;
};

} // namespace Game

#endif // CHARACTER_H
