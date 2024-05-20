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
    explicit CharacterStats(QWidget* parent = nullptr);

protected:
    QWidget* setupClassGroup();
    QWidget* setupGeneralGroup();
    QWidget* setupCombatGroup();
    QWidget* setupBasicGroup();
    QWidget* setupSocialGroup();

private:
    QLabel* m_classIcon;
    QLabel* m_nickname;
    QLabel* m_title;
    QLabel* m_level;
    QLabel* m_clan;
    QLabel* m_class;
    QProgressBar* m_cpBar;
    QProgressBar* m_hpBar;
    QProgressBar* m_mpBar;
    QProgressBar* m_expBar;
    QLabel* m_skillPoints;
    QProgressBar* m_loadBar;
    QLabel* m_pAttack;
    QLabel* m_pDefense;
    QLabel* m_attackSpeed;
    QLabel* m_accuracy;
    QLabel* m_critRate;
    QLabel* m_mAttack;
    QLabel* m_mDefense;
    QLabel* m_castSpeed;
    QLabel* m_evasion;
    QLabel* m_speed;
    QLabel* m_str;
    QLabel* m_int;
    QLabel* m_dex;
    QLabel* m_wit;
    QLabel* m_con;
    QLabel* m_men;
    QLabel* m_karma;
    QLabel* m_pvpCount;
    QLabel* m_pkCount;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // CHARACTER_STATS_H
