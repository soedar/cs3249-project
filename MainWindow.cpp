#include "MainWindow.h"

MainWindow::MainWindow(DatabaseLayer *db)
{
    setGeometry(0,0,800,600);
    this->db = db;
}
