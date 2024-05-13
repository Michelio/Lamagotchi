#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Lamagotchi
{

namespace Ui
{

class SelectedCharacter;
class LoginForm;
class CharacterStats;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    SelectedCharacter* m_selectedCharacter;
    LoginForm* m_loginForm;
    CharacterStats* m_characterStats;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // MAIN_WINDOW_H
