#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "StudentMainWidget.h"

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    StudentWindow();

private:
    StudentMainWidget *mainWidget;

private slots:
void toggleMainWidget();
};

#endif // STUDENTWINDOW_H
