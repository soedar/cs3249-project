#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "DatabaseLayer.h"
#include "MainWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(DatabaseLayer *db, User loggedInUser, MainWidget *mainWidget);
    bool didLoggedOff();
    void setup();

protected:
    MainWidget *mainWidget;
    QWidget *parentWidget;
    DatabaseLayer *db;
    QString email;

private:
    bool loggedOff;

private slots:
    void logoff();

protected slots:
    void showMainWidget();

};

#endif
