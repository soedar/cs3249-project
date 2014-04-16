#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include "DatabaseLayer.h"
#include "MainWindow.h"
#include "StudentMainWidget.h"
#include "StudentLessonWidget.h"
#include "TestWidget.h"

class StudentWindow : public MainWindow
{
    Q_OBJECT
public:
    StudentWindow(DatabaseLayer *db);

private:
    TestWidget *testWidget;
    StudentWindow(DatabaseLayer *db, StudentMainWidget *studentMainWidget);
    StudentMainWidget *studentMainWidget;
    StudentLessonWidget *lessonWidget;

private slots:
    void showLessonWidget(int i);
    void newLessonCreated();
};

#endif // STUDENTWINDOW_H
