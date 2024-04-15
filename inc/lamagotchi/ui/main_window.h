#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Lamagotchi
{

namespace Ui
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

} // namespace Ui
} // namespace Lamagotchi

#endif // MAIN_WINDOW_H
