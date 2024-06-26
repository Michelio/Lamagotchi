#ifndef USER_H
#define USER_H

#include "character.h"

namespace Lamagotchi
{

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
    void setAccuracy(const uint32_t accuracy);
    uint32_t getAccuracy() const;
    void setEvasion(const uint32_t evasion);
    uint32_t getEvasion() const;
    void setCriticalHit(const uint32_t criticalHit);
    uint32_t getCriticalHit() const;
    void setPvpCount(const uint32_t pvpCount);
    uint32_t getPvpCount() const;
    void setPkCount(const uint32_t pkCount);
    uint32_t getPkCount() const;

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
    uint32_t m_accuracy = 0;
    uint32_t m_evasion = 0;
    uint32_t m_criticalHit = 0;
    uint32_t m_pvpCount = 0;
    uint32_t m_pkCount = 0;
};

} // namespace Game
} // namespace Lamagotchi

#endif // USER_H
