#include "ui/form/selected_character.h"

#include <QSizePolicy>

namespace Lamagotchi
{

namespace Ui
{

SelectedCharacter::SelectedCharacter(QWidget* parent) : QWidget{parent}
{
    m_mainLayout = new QGridLayout{this};
    m_nameLabel = new QLabel{"None"};
    m_nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_levelLabel = new QLabel{"lvl."};
    m_levelLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_levelNumberLabel = new QLabel{"00"};
    m_levelNumberLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_combatPointsBar = new QProgressBar;
    m_combatPointsBar->setMinimum(0);
    m_combatPointsBar->setMaximum(100);
    m_combatPointsBar->setValue(100);
    m_combatPointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_healthPointsBar = new QProgressBar;
    m_healthPointsBar->setMinimum(0);
    m_healthPointsBar->setMaximum(100);
    m_healthPointsBar->setValue(100);
    m_healthPointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_manaPointsBar = new QProgressBar;
    m_manaPointsBar->setMinimum(0);
    m_manaPointsBar->setMaximum(100);
    m_manaPointsBar->setValue(100);
    m_manaPointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_experiencePointsBar = new QProgressBar;
    m_experiencePointsBar->setMinimum(0);
    m_experiencePointsBar->setMaximum(100);
    m_experiencePointsBar->setValue(100);
    m_experiencePointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_mainLayout->setVerticalSpacing(5);
    m_mainLayout->addWidget(m_nameLabel, 0, 0, Qt::AlignLeft);
    m_mainLayout->addWidget(m_levelLabel, 0, 1, Qt::AlignCenter);
    m_mainLayout->addWidget(m_levelNumberLabel, 0, 2, Qt::AlignLeft);
    m_mainLayout->addWidget(m_combatPointsBar, 1, 0, 3, 1);
    m_mainLayout->addWidget(m_healthPointsBar, 2, 0, 3, 1);
    m_mainLayout->addWidget(m_manaPointsBar, 3, 0, 3, 1);
    m_mainLayout->addWidget(m_experiencePointsBar, 4, 0, 3, 1);
}

} // namespace Ui
} // namespace Lamagotchi
