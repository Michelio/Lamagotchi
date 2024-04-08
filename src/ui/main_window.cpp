#include "lamagotchi/ui/main_window.h"

#include <QDockWidget>
#include <QGraphicsView>
#include <QListView>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

namespace Ui
{

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QTabWidget* centralTabWidget = new QTabWidget(this);
    QTabBar* packetLogTab = new QTabBar(this);
    QTextEdit* packetLogTextEdit = new QTextEdit(this);
    QTabBar* mapTab = new QTabBar(this);
    QGraphicsView* mapGraphicView = new QGraphicsView(this);
    QListView* accountsListView = new QListView(this);
    QPushButton* addAccountButton = new QPushButton("Add", this);

    centralTabWidget->addTab(packetLogTab, "Packets Log");
    centralTabWidget->addTab(mapTab, "Map");
    centralTabWidget->setMovable(true);

    this->setCentralWidget(centralTabWidget);

    QDockWidget* characterInfoDock = new QDockWidget(tr("Character"), this);
    characterInfoDock->setAllowedAreas(Qt::AllDockWidgetAreas);

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