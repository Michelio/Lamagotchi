#include "ui/main_window.h"
#include "ui/widgets/character_stats.h"
#include "ui/widgets/login_form.h"
#include "ui/widgets/selected_character.h"

#include <QDockWidget>
#include <QMenuBar>
#include <QScrollArea>
#include <QSizePolicy>
#include <QTabWidget>

namespace Lamagotchi
{

namespace Ui
{

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QTabWidget* centralTabWidget = new QTabWidget{this};
    QTabBar* packetLogTab = new QTabBar{this};
    QTabBar* mapTab = new QTabBar{this};
    QMenuBar* menuBar = new QMenuBar{this};

    centralTabWidget->addTab(packetLogTab, "Packets Log");
    centralTabWidget->addTab(mapTab, "Map");
    centralTabWidget->setMovable(true);

    setCentralWidget(centralTabWidget);
    setMenuWidget(menuBar);

    QDockWidget* characterInfoDock = new QDockWidget{"Character", this};
    m_selectedCharacter = new SelectedCharacter{characterInfoDock};
    m_selectedCharacter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    characterInfoDock->setWidget(m_selectedCharacter);
    characterInfoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    characterInfoDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                                   QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::LeftDockWidgetArea, characterInfoDock);

    QDockWidget* characterStatsDock = new QDockWidget{"Status", this};
    m_characterStats = new CharacterStats{characterStatsDock};
    m_characterStats->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QScrollArea* characterStatsScrollArea = new QScrollArea{characterStatsDock};
    characterStatsScrollArea->setWidget(m_characterStats);
    characterStatsScrollArea->setWidgetResizable(true);

    characterStatsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    characterStatsDock->setWidget(characterStatsScrollArea);
    characterStatsDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                                    QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::LeftDockWidgetArea, characterStatsDock);

    QDockWidget* inventoryDock = new QDockWidget{"Inventory", this};
    inventoryDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    inventoryDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                               QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::LeftDockWidgetArea, inventoryDock);

    QMainWindow::tabifyDockWidget(inventoryDock, characterStatsDock);

    QDockWidget* enemyInfoDock = new QDockWidget{"Enemy", this};
    enemyInfoDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    enemyInfoDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                               QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::LeftDockWidgetArea, enemyInfoDock);

    QDockWidget* accountsListDock = new QDockWidget{"Accounts", this};
    accountsListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    accountsListDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                                  QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::RightDockWidgetArea, accountsListDock);

    QDockWidget* loginFormDock = new QDockWidget{this};
    m_loginForm = new LoginForm{loginFormDock};
    m_loginForm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    loginFormDock->setWidget(m_loginForm);
    loginFormDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    loginFormDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                               QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::RightDockWidgetArea, loginFormDock);
}

MainWindow::~MainWindow()
{
}

} // namespace Ui
} // namespace Lamagotchi
