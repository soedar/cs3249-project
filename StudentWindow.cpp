#include "StudentWindow.h"


StudentWindow::StudentWindow()
{
    setGeometry(0,0,800,600);

    mainWidget = new StudentMainWidget();
    toggleMainWidget();
}

void StudentWindow::toggleMainWidget()
{
    setCentralWidget(mainWidget);
    mainWidget->updateTable();
}