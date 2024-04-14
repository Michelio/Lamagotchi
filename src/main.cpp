#include "lamagotchi/bot_client.h"
#include "lamagotchi/ui/main_window.h"

#include <QApplication>

using namespace Lamagotchi;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Ui::MainWindow w;
    BotClient bot;

    w.show();
    return a.exec();
}
