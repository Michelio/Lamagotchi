#ifndef SELECTED_CHARACTER_H
#define SELECTED_CHARACTER_H

#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace Lamagotchi
{

namespace Ui
{

class SelectedCharacter : public QWidget
{
public:
    SelectedCharacter(QWidget* parent = nullptr);

private:
    QGridLayout* m_mainLayout;
    QLabel* m_nameLabel;
    QLabel* m_levelLabel;
    QLabel* m_levelNumberLabel;
    QProgressBar* m_combatPointsBar;
    QProgressBar* m_healthPointsBar;
    QProgressBar* m_manaPointsBar;
    QProgressBar* m_experiencePointsBar;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // SELECTED_CHARACTER_H
