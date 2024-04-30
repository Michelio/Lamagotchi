#include "bot_client.h"
#include "ui/form/login_form.h"
#include "ui/main_window.h"

#include <QApplication>
#include <thread>

using namespace Lamagotchi;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Ui::MainWindow w;
    BotClient bot;

    QObject::connect(w.loginForm, &Ui::LoginForm::credentialsReady, &bot, &BotClient::onCredentialsReady);

    std::jthread thread([&bot]() { bot.run(); });

    w.show();
    return a.exec();
}
