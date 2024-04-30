#include "ui/form/character_stats.h"
#include "ui/layouts/flow_layout.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>

namespace Lamagotchi
{

namespace Ui
{

CharacterStats::CharacterStats(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* m_mainLayout = new QVBoxLayout{this};
    m_classImage = new QLabel;
    m_classImage->setPixmap(QPixmap{"../assets/images/classes/rogue.png"});
    m_classImage->setScaledContents(true);
    m_classImage->setFixedWidth(100);
    m_classImage->setFixedHeight(100);
    m_classImage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_cpBar = new QProgressBar;
    m_cpBar->setMinimum(0);
    m_cpBar->setMaximum(100);
    m_cpBar->setValue(100);
    m_cpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_hpBar = new QProgressBar;
    m_hpBar->setMinimum(0);
    m_hpBar->setMaximum(100);
    m_hpBar->setValue(100);
    m_hpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_mpBar = new QProgressBar;
    m_mpBar->setMinimum(0);
    m_mpBar->setMaximum(100);
    m_mpBar->setValue(100);
    m_mpBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_expBar = new QProgressBar;
    m_expBar->setMinimum(0);
    m_expBar->setMaximum(100);
    m_expBar->setValue(100);
    m_expBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_loadBar = new QProgressBar;
    m_loadBar->setMinimum(0);
    m_loadBar->setMaximum(1000);
    m_loadBar->setValue(1000);
    m_loadBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout* barsLayout = new QVBoxLayout;
    barsLayout->addWidget(m_cpBar);
    barsLayout->addWidget(m_hpBar);
    barsLayout->addWidget(m_mpBar);
    barsLayout->addWidget(m_expBar);
    barsLayout->addWidget(m_loadBar);

    QGridLayout* combatLayout = new QGridLayout;
    QGroupBox* combat = new QGroupBox{"Combat"};
    combat->setLayout(combatLayout);
    combat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_mainLayout->addLayout(barsLayout);
    m_mainLayout->addWidget(m_classImage);
}

} // namespace Ui
} // namespace Lamagotchi
