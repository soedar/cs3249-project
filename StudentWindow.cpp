#include "StudentWindow.h"


StudentWindow::StudentWindow(DatabaseLayer *db)
{
    setGeometry(0,0,800,600);
    this->db = db;

    mainWidget = new StudentMainWidget();
    toggleMainWidget();
}

void StudentWindow::toggleMainWidget()
{
    setCentralWidget(mainWidget);
    mainWidget->updateTable();
}