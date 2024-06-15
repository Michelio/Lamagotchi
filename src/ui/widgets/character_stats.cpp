#include "ui/widgets/character_stats.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>

namespace Lamagotchi
{

namespace Ui
{

CharacterStats::CharacterStats(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout{this};
    mainLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(setupClassGroup());
    mainLayout->addWidget(setupGeneralGroup());
    mainLayout->addWidget(setupCombatGroup());
    mainLayout->addWidget(setupBasicGroup());
    mainLayout->addWidget(setupSocialGroup());
}

QWidget* CharacterStats::setupClassGroup()
{
    QGroupBox* classWidget = new QGroupBox{this};
    QGridLayout* classLayout = new QGridLayout{classWidget};
    classWidget->setLayout(classLayout);

    QPixmap classPixmap{"../assets/images/classes/none.png"};
    m_classIcon = new QLabel{this};
    m_classIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_classIcon->setPixmap(classPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* titleText = new QLabel{"Title:", this};
    titleText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_title = new QLabel{"-", this};
    m_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* nameText = new QLabel{"Name:", this};
    nameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_nickname = new QLabel{"-", this};
    m_nickname->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* clanText = new QLabel{"Clan:", this};
    clanText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_clan = new QLabel{"-", this};
    m_clan->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* classText = new QLabel{"Class:", this};
    classText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_class = new QLabel{"-", this};
    m_class->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* levelText = new QLabel{"Level:", this};
    levelText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_level = new QLabel{"0", this};
    m_level->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    classLayout->addWidget(m_classIcon, 0, 0, 3, 2, Qt::AlignCenter);
    classLayout->addWidget(titleText, 0, 2, Qt::AlignLeft);
    classLayout->addWidget(m_title, 0, 3, Qt::AlignRight);
    classLayout->addWidget(nameText, 1, 2, Qt::AlignLeft);
    classLayout->addWidget(m_nickname, 1, 3, Qt::AlignRight);
    classLayout->addWidget(clanText, 2, 2, Qt::AlignLeft);
    classLayout->addWidget(m_clan, 2, 3, Qt::AlignRight);
    classLayout->addWidget(classText, 3, 0, Qt::AlignLeft);
    classLayout->addWidget(m_class, 3, 1, Qt::AlignLeft);
    classLayout->addWidget(levelText, 3, 2, Qt::AlignLeft);
    classLayout->addWidget(m_level, 3, 3, Qt::AlignRight);

    return classWidget;
}

QWidget* CharacterStats::setupGeneralGroup()
{
    QGroupBox* generalGroupBox = new QGroupBox{this};
    generalGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* generalGroupLayout = new QGridLayout{generalGroupBox};

    QLabel* hpText = new QLabel{"HP", generalGroupBox};
    hpText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_hpBar = new QProgressBar{generalGroupBox};
    m_hpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_hpBar->setMinimum(0);
    m_hpBar->setMaximum(100);
    m_hpBar->setValue(100);

    QLabel* mpText = new QLabel{"MP", generalGroupBox};
    mpText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_mpBar = new QProgressBar{generalGroupBox};
    m_mpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mpBar->setMinimum(0);
    m_mpBar->setMaximum(100);
    m_mpBar->setValue(100);

    QLabel* spText = new QLabel{"SP", generalGroupBox};
    spText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_skillPoints = new QLabel{"0", generalGroupBox};
    m_skillPoints->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_skillPoints->setStyleSheet("background-color: black; color: white;");
    m_skillPoints->setAlignment(Qt::AlignCenter);

    QLabel* cpText = new QLabel{"CP", generalGroupBox};
    cpText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_cpBar = new QProgressBar{generalGroupBox};
    m_cpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_cpBar->setMinimum(0);
    m_cpBar->setMaximum(100);
    m_cpBar->setValue(100);

    QPixmap loadPixmap{"../assets/images/bag-icon.png"};
    QLabel* loadIcon = new QLabel{generalGroupBox};
    loadIcon->setPixmap(loadPixmap.scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    loadIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_loadBar = new QProgressBar{generalGroupBox};
    m_loadBar->setMinimum(0);
    m_loadBar->setMaximum(100);
    m_loadBar->setValue(0);
    m_loadBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* expText = new QLabel{"XP", generalGroupBox};
    expText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_expBar = new QProgressBar{generalGroupBox};
    m_expBar->setMinimum(0);
    m_expBar->setMaximum(100);
    m_expBar->setValue(0);
    m_expBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    generalGroupLayout->addWidget(hpText, 0, 0);
    generalGroupLayout->addWidget(m_hpBar, 0, 1);
    generalGroupLayout->addWidget(mpText, 1, 0);
    generalGroupLayout->addWidget(m_mpBar, 1, 1);
    generalGroupLayout->addWidget(spText, 2, 0);
    generalGroupLayout->addWidget(m_skillPoints, 2, 1);
    generalGroupLayout->addWidget(cpText, 0, 2);
    generalGroupLayout->addWidget(m_cpBar, 0, 3);
    generalGroupLayout->addWidget(loadIcon, 1, 2);
    generalGroupLayout->addWidget(m_loadBar, 1, 3);
    generalGroupLayout->addWidget(expText, 3, 0);
    generalGroupLayout->addWidget(m_expBar, 3, 1, 1, 4);

    return generalGroupBox;
}

QWidget* CharacterStats::setupCombatGroup()
{
    QGroupBox* combatGroupBox = new QGroupBox{"Combat", this};
    combatGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* combatGroupLayout = new QGridLayout{combatGroupBox};
    combatGroupLayout->setHorizontalSpacing(25);

    QLabel* pAttackText = new QLabel{"P. Atk.", combatGroupBox};
    pAttackText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pAttack = new QLabel{"0", combatGroupBox};
    m_pAttack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pAttack->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* pDefenseText = new QLabel{"P. Def.", combatGroupBox};
    pDefenseText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pDefense = new QLabel{"0", combatGroupBox};
    m_pDefense->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pDefense->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* accuracyText = new QLabel{"Accuracy", combatGroupBox};
    accuracyText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_accuracy = new QLabel{"0", combatGroupBox};
    m_accuracy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_accuracy->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* critRateText = new QLabel{"Crit. Rate", combatGroupBox};
    critRateText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_critRate = new QLabel{"0", combatGroupBox};
    m_critRate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_critRate->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* attackSpeedText = new QLabel{"Atk. Spd.", combatGroupBox};
    attackSpeedText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_attackSpeed = new QLabel{"0", combatGroupBox};
    m_attackSpeed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_attackSpeed->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* mAttackText = new QLabel{"M. Atk.", combatGroupBox};
    mAttackText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_mAttack = new QLabel{"0", combatGroupBox};
    m_mAttack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mAttack->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* mDefenseText = new QLabel{"M. Def.", combatGroupBox};
    mDefenseText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_mDefense = new QLabel{"0", combatGroupBox};
    m_mDefense->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_mDefense->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* evasionText = new QLabel{"Evasion", combatGroupBox};
    evasionText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_evasion = new QLabel{"0", combatGroupBox};
    m_evasion->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_evasion->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* speedText = new QLabel{"Speed", combatGroupBox};
    speedText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_speed = new QLabel{"0", combatGroupBox};
    m_speed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_speed->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* castSpeedText = new QLabel{"Casting Spd.", combatGroupBox};
    castSpeedText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_castSpeed = new QLabel{"0", combatGroupBox};
    m_castSpeed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_castSpeed->setTextInteractionFlags(Qt::TextSelectableByMouse);

    combatGroupLayout->addWidget(pAttackText, 0, 0);
    combatGroupLayout->addWidget(m_pAttack, 0, 1, Qt::AlignRight);
    combatGroupLayout->addWidget(pDefenseText, 1, 0);
    combatGroupLayout->addWidget(m_pDefense, 1, 1, Qt::AlignRight);
    combatGroupLayout->addWidget(accuracyText, 2, 0);
    combatGroupLayout->addWidget(m_accuracy, 2, 1, Qt::AlignRight);
    combatGroupLayout->addWidget(critRateText, 3, 0);
    combatGroupLayout->addWidget(m_critRate, 3, 1, Qt::AlignRight);
    combatGroupLayout->addWidget(attackSpeedText, 4, 0);
    combatGroupLayout->addWidget(m_attackSpeed, 4, 1, Qt::AlignRight);

    combatGroupLayout->addWidget(mAttackText, 0, 2);
    combatGroupLayout->addWidget(m_mAttack, 0, 3, Qt::AlignRight);
    combatGroupLayout->addWidget(mDefenseText, 1, 2);
    combatGroupLayout->addWidget(m_mDefense, 1, 3, Qt::AlignRight);
    combatGroupLayout->addWidget(evasionText, 2, 2);
    combatGroupLayout->addWidget(m_evasion, 2, 3, Qt::AlignRight);
    combatGroupLayout->addWidget(speedText, 3, 2);
    combatGroupLayout->addWidget(m_speed, 3, 3, Qt::AlignRight);
    combatGroupLayout->addWidget(castSpeedText, 4, 2);
    combatGroupLayout->addWidget(m_castSpeed, 4, 3, Qt::AlignRight);

    return combatGroupBox;
}

QWidget* CharacterStats::setupBasicGroup()
{
    QGroupBox* basicGroupBox = new QGroupBox{"Base", this};
    basicGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* basicGroupLayout = new QGridLayout{basicGroupBox};
    basicGroupLayout->setHorizontalSpacing(25);

    QLabel* strText = new QLabel{"STR", basicGroupBox};
    strText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_str = new QLabel{"0", basicGroupBox};
    m_str->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_str->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* intText = new QLabel{"INT", basicGroupBox};
    intText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_int = new QLabel{"0", basicGroupBox};
    m_int->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_int->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* dexText = new QLabel{"DEX", basicGroupBox};
    dexText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_dex = new QLabel{"0", basicGroupBox};
    m_dex->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_dex->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* witText = new QLabel{"WIT", basicGroupBox};
    witText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_wit = new QLabel{"0", basicGroupBox};
    m_wit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_wit->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* conText = new QLabel{"CON", basicGroupBox};
    conText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_con = new QLabel{"0", basicGroupBox};
    m_con->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_con->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* menText = new QLabel{"MEN", basicGroupBox};
    menText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_men = new QLabel{"0", basicGroupBox};
    m_men->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_men->setTextInteractionFlags(Qt::TextSelectableByMouse);

    basicGroupLayout->addWidget(strText, 0, 0);
    basicGroupLayout->addWidget(m_str, 0, 1, Qt::AlignRight);
    basicGroupLayout->addWidget(intText, 1, 0);
    basicGroupLayout->addWidget(m_int, 1, 1, Qt::AlignRight);

    basicGroupLayout->addWidget(dexText, 0, 2);
    basicGroupLayout->addWidget(m_dex, 0, 3, Qt::AlignRight);
    basicGroupLayout->addWidget(witText, 1, 2);
    basicGroupLayout->addWidget(m_wit, 1, 3, Qt::AlignRight);

    basicGroupLayout->addWidget(conText, 0, 4);
    basicGroupLayout->addWidget(m_con, 0, 5, Qt::AlignRight);
    basicGroupLayout->addWidget(menText, 1, 4);
    basicGroupLayout->addWidget(m_men, 1, 5, Qt::AlignRight);

    return basicGroupBox;
}

QWidget* CharacterStats::setupSocialGroup()
{
    QGroupBox* socialGroupBox = new QGroupBox{"Social", this};
    socialGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* socialGroupLayout = new QGridLayout{socialGroupBox};
    socialGroupLayout->setHorizontalSpacing(25);

    QLabel* karmaText = new QLabel{"Karma", socialGroupBox};
    karmaText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_karma = new QLabel{"0", socialGroupBox};
    m_karma->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_karma->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* pvpText = new QLabel{"PvP", socialGroupBox};
    pvpText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pvpCount = new QLabel{"0", socialGroupBox};
    m_pvpCount->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pvpCount->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QLabel* pkText = new QLabel{"Pk", socialGroupBox};
    pkText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pkCount = new QLabel{"0", socialGroupBox};
    m_pkCount->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pkCount->setTextInteractionFlags(Qt::TextSelectableByMouse);

    socialGroupLayout->addWidget(karmaText, 0, 0);
    socialGroupLayout->addWidget(m_karma, 0, 1, Qt::AlignRight);
    socialGroupLayout->addWidget(pvpText, 0, 2);
    socialGroupLayout->addWidget(m_pvpCount, 0, 3, Qt::AlignRight);
    socialGroupLayout->addWidget(pkText, 0, 4);
    socialGroupLayout->addWidget(m_pkCount, 0, 5, Qt::AlignRight);

    return socialGroupBox;
}

} // namespace Ui
} // namespace Lamagotchi
