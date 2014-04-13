#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include "DatabaseLayer.h"
#include "MainWindow.h"
#include "StudentMainWidget.h"

class StudentWindow : public MainWindow
{
    Q_OBJECT
public:
    StudentWindow(DatabaseLayer *db);

private:
    StudentMainWidget *mainWidget;

private slots:
void toggleMainWidget();
};

#endif // STUDENTWINDOW_H
