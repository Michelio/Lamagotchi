#include "ui/widgets/selected_enemy.h"

#include <QSizePolicy>

namespace Lamagotchi
{

namespace Ui
{

SelectedEnemy::SelectedEnemy(QWidget* parent) : QWidget{parent}
{
    QGridLayout* mainLayout = new QGridLayout{this};

    m_nameLabel = new QLabel{"None", this};
    m_nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel* levelTextLabel = new QLabel{"lvl.", this};
    levelTextLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_levelLabel = new QLabel{"0", this};
    m_levelLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_healthPointsBar = new QProgressBar{this};
    m_healthPointsBar->setMinimum(0);
    m_healthPointsBar->setMaximum(100);
    m_healthPointsBar->setValue(100);
    m_healthPointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_manaPointsBar = new QProgressBar{this};
    m_manaPointsBar->setMinimum(0);
    m_manaPointsBar->setMaximum(100);
    m_manaPointsBar->setValue(100);
    m_manaPointsBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mainLayout->setVerticalSpacing(3);
    mainLayout->addWidget(m_nameLabel, 0, 0);
    mainLayout->addWidget(levelTextLabel, 0, 1, Qt::AlignRight);
    mainLayout->addWidget(m_levelLabel, 0, 2, Qt::AlignLeft);
    mainLayout->addWidget(m_healthPointsBar, 2, 0, 1, 3);
    mainLayout->addWidget(m_manaPointsBar, 3, 0, 1, 3);
}

} // namespace Ui
} // namespace Lamagotchi
