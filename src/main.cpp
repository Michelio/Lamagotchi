#include "lamagotchi/bot_client.h"
#include "lamagotchi/ui/main_window.h"

#include <QApplication>
#include <thread>

#include <boost/thread/thread_pool.hpp>

using namespace Lamagotchi;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Ui::MainWindow w;
    BotClient bot;

    std::jthread t([&bot]() { bot.run(); });

    w.show();
    return a.exec();
}
