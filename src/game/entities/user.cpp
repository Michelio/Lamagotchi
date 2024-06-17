#include "game/entities/user.h"

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

void User::setPAccuracy(const uint32_t pAccuracy)
{
    m_pAccuracy = pAccuracy;
}

uint32_t User::getPAccuracy() const
{
    return m_pAccuracy;
}

void User::setMAccuracy(const uint32_t mAccuracy)
{
    m_mAccuracy = mAccuracy;
}

uint32_t User::getMAccuracy() const
{
    return m_mAccuracy;
}

void User::setPEvasion(const uint32_t pEvasion)
{
    m_pEvasion = pEvasion;
}

uint32_t User::getPEvasion() const
{
    return m_pEvasion;
}

void User::setMEvasion(const uint32_t mEvasion)
{
    m_mEvasion = mEvasion;
}

uint32_t User::getMEvasion() const
{
    return m_mEvasion;
}

void User::setPCriticalHit(const uint32_t pCriticalHit)
{
    m_pCriticalHit = pCriticalHit;
}

uint32_t User::getPCriticalHit() const
{
    return m_pCriticalHit;
}

void User::setMCriticalHit(const uint32_t mCriticalHit)
{
    m_mCriticalHit = mCriticalHit;
}

uint32_t User::getMCriticalHit() const
{
    return m_mCriticalHit;
}

} // namespace Game
