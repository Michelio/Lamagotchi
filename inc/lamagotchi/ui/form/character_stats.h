#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace Lamagotchi
{

namespace Ui
{

class FlowLayout;

class CharacterStats : public QWidget
{
public:
    CharacterStats(QWidget* parent = nullptr);

private:
    QLabel* m_classImage;
    QProgressBar* m_cpBar;
    QProgressBar* m_hpBar;
    QProgressBar* m_mpBar;
    QProgressBar* m_expBar;
    QProgressBar* m_loadBar;
    QLabel* m_nickname;
    QLabel* m_title;
    QLabel* m_level;
    QLabel* m_clan;
    QLabel* m_pAttack;
    QLabel* m_pDefense;
    QLabel* m_accuracy;
    QLabel* m_critRate;
    QLabel* m_pAttackSpeed;
    QLabel* m_mAttack;
    QLabel* m_mDefense;
    QLabel* m_evasion;
    QLabel* m_speed;
    QLabel* m_mAttackSpeed;
    QLabel* m_STR;
    QLabel* m_INT;
    QLabel* m_DEX;
    QLabel* m_WIT;
    QLabel* m_CON;
    QLabel* m_MEN;
    QLabel* m_karma;
    QLabel* m_pvpCount;
    QLabel* m_pkCount;
    QLabel* m_skillPoints;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // CHARACTER_STATS_H
