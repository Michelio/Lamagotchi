#include "game/entities/user.h"

namespace Lamagotchi
{

namespace Game
{

User::User(const uint32_t objectId, std::wstring_view objectName, const Vector3D position, bool isAlive = false)
    : Character{objectId, objectName, position, isAlive}
{
}

void User::setSTR(const uint32_t STR)
{
    m_STR = STR;
}

uint32_t User::getSTR() const
{
    return m_STR;
}

void User::setDEX(const uint32_t DEX)
{
    m_DEX = DEX;
}

uint32_t User::getDEX() const
{
    return m_DEX;
}

void User::setCON(const uint32_t CON)
{
    m_CON = CON;
}

uint32_t User::getCON() const
{
    return m_CON;
}

void User::setINT(const uint32_t INT)
{
    m_INT = INT;
}

uint32_t User::getINT() const
{
    return m_INT;
}

void User::setWIT(const uint32_t WIT)
{
    m_WIT = WIT;
}

uint32_t User::getWIT() const
{
    return m_WIT;
}

void User::setMEN(const uint32_t MEN)
{
    m_MEN = MEN;
}

uint32_t User::getMEN() const
{
    return m_MEN;
}

void User::setPAttack(const uint32_t pAttack)
{
    m_pAttack = pAttack;
}

uint32_t User::getPAttack() const
{
    return m_pAttack;
}

void User::setMAttack(const uint32_t mAttack)
{
    m_mAttack = mAttack;
}

uint32_t User::getMAttack() const
{
    return m_mAttack;
}

void User::setPDefense(const uint32_t pDefense)
{
    m_pDefense = pDefense;
}

uint32_t User::getPDefense() const
{
    return m_pDefense;
}

void User::setMDefense(const uint32_t mDefense)
{
    m_mDefense = mDefense;
}

uint32_t User::getMDefense() const
{
    return m_mDefense;
}

void User::setAccuracy(const uint32_t accuracy)
{
    m_accuracy = accuracy;
}

uint32_t User::getAccuracy() const
{
    return m_accuracy;
}

void User::setEvasion(const uint32_t evasion)
{
    m_evasion = evasion;
}

uint32_t User::getEvasion() const
{
    return m_evasion;
}

void User::setCriticalHit(const uint32_t criticalHit)
{
    m_criticalHit = criticalHit;
}

uint32_t User::getCriticalHit() const
{
    return m_criticalHit;
}

void User::setPvpCount(const uint32_t pvpCount)
{
    m_pvpCount = pvpCount;
}

uint32_t User::getPvpCount() const
{
    return m_pvpCount;
}

void User::setPkCount(const uint32_t pkCount)
{
    m_pkCount = pkCount;
}

uint32_t User::getPkCount() const
{
    return m_pkCount;
}

} // namespace Game
} // namespace Lamagotchi
