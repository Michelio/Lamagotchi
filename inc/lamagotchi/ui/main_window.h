#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Lamagotchi
{

namespace Ui
{

class CharacterInfo;
class LoginForm;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    CharacterInfo* characterInfo;
    LoginForm* loginForm;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // MAIN_WINDOW_H
