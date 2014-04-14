#include "MainWindow.h"

MainWindow::MainWindow(DatabaseLayer *db, MainWidget *mainWidget)
{
    setGeometry(0,0,800,600);
    this->db = db;
    this->mainWidget = mainWidget;

    this->parentWidget = new QWidget();
    this->parentWidget->setLayout(new QHBoxLayout());

    loggedOff = false;

    QObject::connect(mainWidget->logOutButton,SIGNAL(clicked()),this,SLOT(logoff()));
    MenuWidget *menuWidget = new MenuWidget();
    this->parentWidget->layout()->addWidget(menuWidget);

    setCentralWidget(parentWidget);
    showMainWidget();
}

void MainWindow::showMainWidget()
{
    this->parentWidget->layout()->addWidget(mainWidget);
    mainWidget->updateTable();
}


void MainWindow::logoff()
{
    loggedOff = true;
    close();
}

bool MainWindow::didLoggedOff() 
{
    return loggedOff;
}