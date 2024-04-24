#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace Lamagotchi
{

namespace Ui
{

class CharacterInfo : public QWidget
{
    Q_OBJECT
public:
    CharacterInfo(QWidget* parent = nullptr);

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

#endif // CHARACTER_INFO_H
