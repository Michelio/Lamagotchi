
#ifndef SELECTED_ENEMY_H
#define SELECTED_ENEMY_H

#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

namespace Lamagotchi
{

namespace Ui
{

class SelectedEnemy : public QWidget
{
  public:
    SelectedEnemy(QWidget* parent = nullptr);

  private:
    QLabel* m_nameLabel;
    QLabel* m_levelLabel;
    QProgressBar* m_healthPointsBar;
    QProgressBar* m_manaPointsBar;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // SELECTED_ENEMY_H
