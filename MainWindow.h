#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DatabaseLayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(DatabaseLayer *db);

private:
    DatabaseLayer *db;
};

#endif