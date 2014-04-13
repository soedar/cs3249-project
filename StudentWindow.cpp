#include "StudentWindow.h"


StudentWindow::StudentWindow(DatabaseLayer *db) : MainWindow(db, new StudentMainWidget())
{
    this->studentMainWidget = (StudentMainWidget *)mainWidget;
}
