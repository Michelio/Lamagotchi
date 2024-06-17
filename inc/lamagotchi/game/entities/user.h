#ifndef USER_H
#define USER_H

#include "character.h"

namespace Game
{

class User : public Character
{
public:
    User() = default;
    explicit User(const uint32_t objectId, std::wstring_view objectName, const Vector3D position, bool isAlive);

    void setSTR(const uint32_t STR);
    uint32_t getSTR() const;
    void setDEX(const uint32_t DEX);
    uint32_t getDEX() const;
    void setCON(const uint32_t CON);
    uint32_t getCON() const;
    void setINT(const uint32_t INT);
    uint32_t getINT() const;
    void setWIT(const uint32_t WIT);
    uint32_t getWIT() const;
    void setMEN(const uint32_t MEN);
    uint32_t getMEN() const;
    void setPAttack(const uint32_t pAttack);
    uint32_t getPAttack() const;
    void setMAttack(const uint32_t mAttack);
    uint32_t getMAttack() const;
    void setPDefense(const uint32_t pDefense);
    uint32_t getPDefense() const;
    void setMDefense(const uint32_t mDefense);
    uint32_t getMDefense() const;
    void setPAccuracy(const uint32_t pAccuracy);
    uint32_t getPAccuracy() const;
    void setMAccuracy(const uint32_t mAccuracy);
    uint32_t getMAccuracy() const;
    void setPEvasion(const uint32_t pEvasion);
    uint32_t getPEvasion() const;
    void setMEvasion(const uint32_t mEvasion);
    uint32_t getMEvasion() const;
    void setPCriticalHit(const uint32_t pCriticalHit);
    uint32_t getPCriticalHit() const;
    void setMCriticalHit(const uint32_t mCriticalHit);
    uint32_t getMCriticalHit() const;

private:
    uint32_t m_STR = 0;
    uint32_t m_DEX = 0;
    uint32_t m_CON = 0;
    uint32_t m_INT = 0;
    uint32_t m_WIT = 0;
    uint32_t m_MEN = 0;
    uint32_t m_pAttack = 0;
    uint32_t m_mAttack = 0;
    uint32_t m_pDefense = 0;
    uint32_t m_mDefense = 0;
    uint32_t m_pAccuracy = 0;
    uint32_t m_mAccuracy = 0;
    uint32_t m_pEvasion = 0;
    uint32_t m_mEvasion = 0;
    uint32_t m_pCriticalHit = 0;
    uint32_t m_mCriticalHit = 0;
};

} // namespace Game

#endif // USER_H
