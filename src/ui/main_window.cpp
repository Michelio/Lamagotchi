#include "ui/main_window.h"
#include "ui/widgets/character_info.h"

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
    QTabWidget* centralTabWidget = new QTabWidget(this);
    QTabBar* packetLogTab = new QTabBar;
    QTextEdit* packetLogTextEdit = new QTextEdit;
    QTabBar* mapTab = new QTabBar;
    QGraphicsView* mapGraphicView = new QGraphicsView;
    QListView* accountsListView = new QListView;
    QPushButton* addAccountButton = new QPushButton("Add");
    QMenuBar* menuBar = new QMenuBar(this);
    CharacterInfo* charInfo = new CharacterInfo{this};
    charInfo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    centralTabWidget->addTab(packetLogTab, "Packets Log");
    centralTabWidget->addTab(mapTab, "Map");
    centralTabWidget->setMovable(true);

    this->setCentralWidget(centralTabWidget);
    this->setMenuWidget(menuBar);

    QDockWidget* characterInfoDock = new QDockWidget(tr("Character"), this);
    characterInfoDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    characterInfoDock->setWidget(charInfo);

    QDockWidget* inventoryDock = new QDockWidget(tr("Inventory"), this);
    inventoryDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    QDockWidget* enemyInfoDock = new QDockWidget(tr("Enemy"), this);
    enemyInfoDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    QDockWidget* accountsListDock = new QDockWidget(tr("Accounts"), this);
    accountsListDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    QWidget* accountsWidget = new QWidget();
    QVBoxLayout* accountsLayout = new QVBoxLayout();
    accountsLayout->addWidget(accountsListView);
    accountsLayout->addWidget(addAccountButton);
    accountsWidget->setLayout(accountsLayout);
    accountsListDock->setWidget(accountsWidget);

    this->addDockWidget(Qt::LeftDockWidgetArea, characterInfoDock);
    this->addDockWidget(Qt::LeftDockWidgetArea, inventoryDock);
    this->addDockWidget(Qt::LeftDockWidgetArea, enemyInfoDock);
    this->addDockWidget(Qt::RightDockWidgetArea, accountsListDock);
}

MainWindow::~MainWindow()
{
}

} // namespace Ui
} // namespace Lamagotchi
