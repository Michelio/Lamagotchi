#include "bot_client.h"
#include "ui/main_window.h"

#include <QApplication>
#include <thread>

using namespace Lamagotchi;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Ui::MainWindow w;
    BotClient bot;
    std::jthread thread([&bot]() { bot.run(); });

    w.show();
    return a.exec();
}
