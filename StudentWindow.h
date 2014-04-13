#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "DatabaseLayer.h"
#include "StudentMainWidget.h"

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    StudentWindow(DatabaseLayer *db);

private:
    StudentMainWidget *mainWidget;
    DatabaseLayer *db;

private slots:
void toggleMainWidget();
};

#endif // STUDENTWINDOW_H
