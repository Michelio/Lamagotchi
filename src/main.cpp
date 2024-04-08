#include "lamagotchi/network/tcp_client.h"
#include "lamagotchi/ui/main_window.h"

#include <QApplication>
#include <thread>

#include <boost/thread/thread_pool.hpp>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Network::TcpClient client{"192.168.88.19", 2106};

    client.connect();
    client.connect();

    std::jthread t1([&client]() { client.run(); });

    w.show();
    return a.exec();
}
