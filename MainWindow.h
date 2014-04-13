#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DatabaseLayer.h"
#include "MainWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(DatabaseLayer *db, MainWidget *mainWidget);
    bool didLoggedOff();
    void setup();

protected:
    MainWidget *mainWidget;
    DatabaseLayer *db;

private:
    bool loggedOff;

private slots:
    void logoff();

protected slots:
    void showMainWidget();

};

#endif