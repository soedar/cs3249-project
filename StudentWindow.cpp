#include "StudentWindow.h"


StudentWindow::StudentWindow(DatabaseLayer *db) : MainWindow(db)
{
    mainWidget = new StudentMainWidget();
    toggleMainWidget();
}

void StudentWindow::toggleMainWidget()
{
    setCentralWidget(mainWidget);
    mainWidget->updateTable();
}