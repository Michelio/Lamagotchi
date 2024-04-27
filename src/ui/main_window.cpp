#include "ui/main_window.h"
#include "ui/widgets/character_info.h"
#include "ui/widgets/login_form.h"

#include <QDockWidget>
#include <QGraphicsView>
#include <QListView>
#include <QMenuBar>
#include <QPushButton>
#include <QSizePolicy>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

namespace Lamagotchi
{

namespace Ui
{

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QTabWidget* centralTabWidget = new QTabWidget;
    QTabBar* packetLogTab = new QTabBar;
    QTextEdit* packetLogTextEdit = new QTextEdit;
    QTabBar* mapTab = new QTabBar;
    QGraphicsView* mapGraphicView = new QGraphicsView;
    QListView* accountsListView = new QListView;
    QMenuBar* menuBar = new QMenuBar;
    characterInfo = new CharacterInfo;
    characterInfo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    loginForm = new LoginForm;
    loginForm->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    centralTabWidget->addTab(packetLogTab, "Packets Log");
    centralTabWidget->addTab(mapTab, "Map");
    centralTabWidget->setMovable(true);

    this->setCentralWidget(centralTabWidget);
    this->setMenuWidget(menuBar);

    QDockWidget* characterInfoDock = new QDockWidget{"Character"};
    characterInfoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    characterInfoDock->setWidget(characterInfo);

    QDockWidget* inventoryDock = new QDockWidget{"Inventory"};
    inventoryDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QDockWidget* enemyInfoDock = new QDockWidget{"Enemy"};
    enemyInfoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QDockWidget* accountsListDock = new QDockWidget{"Accounts"};
    accountsListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QDockWidget* loginFormDock = new QDockWidget{};
    loginFormDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    loginFormDock->setWidget(loginForm);

    QWidget* accountsWidget = new QWidget();
    QVBoxLayout* accountsLayout = new QVBoxLayout();
    accountsLayout->addWidget(accountsListView);
    accountsWidget->setLayout(accountsLayout);
    accountsListDock->setWidget(accountsWidget);

    this->addDockWidget(Qt::LeftDockWidgetArea, characterInfoDock);
    this->addDockWidget(Qt::LeftDockWidgetArea, inventoryDock);
    this->addDockWidget(Qt::LeftDockWidgetArea, enemyInfoDock);
    this->addDockWidget(Qt::RightDockWidgetArea, accountsListDock);
    this->addDockWidget(Qt::RightDockWidgetArea, loginFormDock);
}

MainWindow::~MainWindow()
{
}

} // namespace Ui
} // namespace Lamagotchi
