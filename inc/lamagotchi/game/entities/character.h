#ifndef CHARACTER_H
#define CHARACTER_H

#include "live_entity.h"

namespace Lamagotchi
{

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
    void setKarma(const uint32_t karma);
    uint32_t getKarma() const;
    void setRace(const uint8_t race);
    uint8_t getRace() const;
    void setSex(const uint8_t sex);
    uint8_t getSex() const;
    void setHero(const uint8_t hero);
    uint8_t getHero() const;
    void setNoble(const uint8_t noble);
    uint8_t getNoble() const;
    void setPvpStatus(const uint8_t status);
    uint8_t getPvpStatus() const;

protected:
    uint32_t m_classId = 0;
    uint32_t m_mainClassId = 0;
    uint32_t m_currentCombatPoints = 0;
    uint32_t m_maximumCombatPoints = 0;
    uint32_t m_karma = 0;
    uint8_t m_race = 0;
    uint8_t m_sex = 0;
    uint8_t m_hero = 0;
    uint8_t m_noble = 0;
    uint8_t m_pvpStatus = 0;
};

} // namespace Game
} // namespace Lamagotchi

#endif // CHARACTER_H
