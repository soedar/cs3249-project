#include "MainWindow.h"

MainWindow::MainWindow(DatabaseLayer *db, MainWidget *mainWidget)
{
    setGeometry(0,0,800,600);
    this->db = db;
    this->mainWidget = mainWidget;

    loggedOff = false;

    QObject::connect(mainWidget->logOutButton,SIGNAL(clicked()),this,SLOT(logoff()));

    showMainWidget();
    
    this->menuWidget = new MenuWidget(this->mainWidget, db);
    this->menuWidget->show();
}

void MainWindow::showMainWidget()
{
    mainWidget->updateTable();
    mainWidget->show();
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

void MainWindow::resizeEvent(QResizeEvent *event) 
{
    this->menuWidget->adjustSize();
}
