#ifndef LIVE_ENTITY_H
#define LIVE_ENTITY_H

#include "entity.h"
#include <cstdint>
#include <string_view>
#include <sys/types.h>

namespace Game
{

class LiveEntity : public Entity
{
public:
    LiveEntity() = default;
    explicit LiveEntity(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                        const bool isAlive);

    void setExperience(const uint32_t experience);
    uint32_t getExperience() const;
    void setSkillPoints(const uint32_t skillPoints);
    uint32_t getSkillPoints() const;
    void setLevel(const uint8_t level);
    uint8_t getLevel() const;
    void setCurrentHealthPoints(const uint32_t currentHealthPoints);
    uint32_t getCurrentHealthPoints() const;
    void setCurrentManaPoints(const uint32_t currentManaPoints);
    uint32_t getCurrentManaPoints() const;
    void setMaximumHealthPoints(const uint32_t maximumHealthPoints);
    uint32_t getMaximumHealthPoints() const;
    void setMaximumManaPoints(const uint32_t maximumManaPoints);
    uint32_t getMaximumManaPoints() const;
    void setSpeed(const uint32_t speed);
    uint32_t getSpeed() const;
    void setAttackSpeed(const uint32_t attackSpeed);
    uint32_t getAttackSpeed() const;
    void setCastingSpeed(const uint32_t castingSpeed);
    uint32_t getCastingSpeed() const;
    void setLoad(const uint32_t load);
    uint32_t getLoad() const;
    bool getIsAlive() const;
    void setIsAlive(const bool isAlive);

protected:
    uint32_t m_experience = 0;
    uint32_t m_skillPoints = 0;
    uint32_t m_currentHealthPoints = 0;
    uint32_t m_currentManaPoints = 0;
    uint32_t m_maximumHealthPoints = 0;
    uint32_t m_maximumManaPoints = 0;
    uint32_t m_speed = 0;
    uint32_t m_attackSpeed = 0;
    uint32_t m_castingSpeed = 0;
    uint32_t m_load = 0;
    uint8_t m_level = 0;
    bool m_isAlive;
};

} // namespace Game

#endif // LIVE_ENTITY_H
