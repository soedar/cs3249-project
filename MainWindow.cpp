#include "MainWindow.h"

MainWindow::MainWindow(DatabaseLayer *db, User loggedInUser, MainWidget *mainWidget)
{
    setGeometry(0,0,800,600);
    this->email = loggedInUser.email();
    this->db = db;
    this->mainWidget = mainWidget;

    loggedOff = false;

    QObject::connect(mainWidget->logOutButton,SIGNAL(clicked()),this,SLOT(logoff()));

    showMainWidget();
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
    mainWidget->close();
}

bool MainWindow::didLoggedOff() 
{
    return loggedOff;
}


