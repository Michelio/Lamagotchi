#include "game/entities/character.h"

namespace Lamagotchi
{

namespace Game
{

Character::Character(const uint32_t objectId, std::wstring_view objectName, const Vector3D position,
                     const bool isAlive = false)
    : LiveEntity{objectId, objectName, position, isAlive}
{
}

void Character::setCurrentCombatPoints(const uint32_t currentCombatPoints)
{
    m_currentCombatPoints = currentCombatPoints;
}

uint32_t Character::getCurrentCombatPoints() const
{
    return m_currentCombatPoints;
}

void Character::setMaximumCombatPoints(const uint32_t maximumCombatPoints)
{
    m_maximumCombatPoints = maximumCombatPoints;
}

uint32_t Character::getMaximumCombatPoints() const
{
    return m_maximumCombatPoints;
}

void Character::setClassId(const uint32_t classId)
{
    m_classId = classId;
}

uint32_t Character::getClassId() const
{
    return m_classId;
}

void Character::setMainClassId(const uint32_t mainClassId)
{
    m_mainClassId = mainClassId;
}

uint32_t Character::getMainClassId() const
{
    return m_mainClassId;
}

void Character::setKarma(const uint32_t karma)
{
    m_karma = karma;
}

uint32_t Character::getKarma() const
{
    return m_karma;
}

void Character::setRace(const uint8_t race)
{
    m_race = race;
}

uint8_t Character::getRace() const
{
    return m_race;
}

void Character::setSex(const uint8_t sex)
{
    m_sex = sex;
}

uint8_t Character::getSex() const
{
    return m_sex;
}

void Character::setHero(const uint8_t hero)
{
    m_hero = hero;
}

uint8_t Character::getHero() const
{
    return m_hero;
}

void Character::setNoble(const uint8_t noble)
{
    m_noble = noble;
}

uint8_t Character::getNoble() const
{
    return m_noble;
}

void Character::setPvpStatus(const uint8_t status)
{
    m_pvpStatus = status;
}

uint8_t Character::getPvpStatus() const
{
    return m_pvpStatus;
}

} // namespace Game
} // namespace Lamagotchi
