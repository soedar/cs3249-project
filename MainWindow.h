#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "DatabaseLayer.h"
#include "MainWidget.h"
#include "MenuWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(DatabaseLayer *db, MainWidget *mainWidget);
    bool didLoggedOff();
    void setup();

protected:
    MainWidget *mainWidget;
    QWidget *parentWidget;
    DatabaseLayer *db;
    MenuWidget *menuWidget;
    void resizeEvent(QResizeEvent *event);

private:
    bool loggedOff;

private slots:
    void logoff();

protected slots:
    void showMainWidget();

};

#endif
