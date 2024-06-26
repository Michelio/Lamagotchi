#include "game/entities/live_entity.h"

namespace Lamagotchi
{

namespace Game
{

LiveEntity::LiveEntity(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                       const bool isAlive = false)
    : Entity{objectId, objectName, position}, m_isAlive(isAlive)
{
}

void LiveEntity::setExperience(const uint32_t experience)
{
    m_experience = experience;
}

uint32_t LiveEntity::getExperience() const
{
    return m_experience;
}

void LiveEntity::setSkillPoints(const uint32_t skillPoints)
{
    m_skillPoints = skillPoints;
}

uint32_t LiveEntity::getSkillPoints() const
{
    return m_skillPoints;
}

void LiveEntity::setLevel(const uint8_t level)
{
    m_level = level;
}

uint8_t LiveEntity::getLevel() const
{
    return m_level;
}

void LiveEntity::setCurrentHealthPoints(const uint32_t currentHealthPoints)
{
    m_currentHealthPoints = currentHealthPoints;
}

uint32_t LiveEntity::getCurrentHealthPoints() const
{
    return m_currentHealthPoints;
}

void LiveEntity::setCurrentManaPoints(const uint32_t currentManaPoints)
{
    m_currentManaPoints = currentManaPoints;
}

uint32_t LiveEntity::getCurrentManaPoints() const
{
    return m_currentManaPoints;
}

void LiveEntity::setMaximumHealthPoints(const uint32_t maximumHealthPoints)
{
    m_maximumHealthPoints = maximumHealthPoints;
}

uint32_t LiveEntity::getMaximumHealthPoints() const
{
    return m_maximumHealthPoints;
}

void LiveEntity::setMaximumManaPoints(const uint32_t maximumManaPoints)
{
    m_maximumManaPoints = maximumManaPoints;
}

uint32_t LiveEntity::getMaximumManaPoints() const
{
    return m_maximumManaPoints;
}

void LiveEntity::setRunningSpeed(const uint32_t runningSpeed)
{
    m_runningSpeed = runningSpeed;
}

uint32_t LiveEntity::getRunningSpeed() const
{
    return m_runningSpeed;
}

void LiveEntity::setWalkingSpeed(const uint32_t walkingSpeed)
{
    m_walkingSpeed = walkingSpeed;
}

uint32_t LiveEntity::getWalkingSpeed() const
{
    return m_walkingSpeed;
}

void LiveEntity::setAttackSpeed(const uint32_t attackSpeed)
{
    m_attackSpeed = attackSpeed;
}

uint32_t LiveEntity::getAttackSpeed() const
{
    return m_attackSpeed;
}

void LiveEntity::setCastingSpeed(const uint32_t castingSpeed)
{
    m_castingSpeed = castingSpeed;
}

uint32_t LiveEntity::getCastingSpeed() const
{
    return m_castingSpeed;
}

void LiveEntity::setLoad(const uint32_t load)
{
    m_load = load;
}

uint32_t LiveEntity::getLoad() const
{
    return m_load;
}

void LiveEntity::setMaximumLoad(const uint32_t load)
{
    m_maximumLoad = load;
}

uint32_t LiveEntity::getMaximumLoad() const
{
    return m_maximumLoad;
}

bool LiveEntity::getIsAlive() const
{
    return m_isAlive;
}

void LiveEntity::setIsAlive(const bool isAlive)
{
    m_isAlive = isAlive;
}

} // namespace Game
} // namespace Lamagotchi
