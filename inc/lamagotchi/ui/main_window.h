#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui/widgets/login_form.h"

#include <QMainWindow>

namespace Lamagotchi
{

namespace Ui
{

class LoginForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    LoginForm* loginForm;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // MAIN_WINDOW_H
