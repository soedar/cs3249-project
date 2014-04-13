#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include "TeacherMainWidget.h"
#include "AddLessonWidget.h"
#include "MainWindow.h"
#include "DatabaseLayer.h"

class TeacherWindow : public MainWindow
{
    Q_OBJECT
public:
    TeacherWindow(DatabaseLayer *db);

private:
    TeacherMainWidget *teacherMainWidget;
    AddLessonWidget *addWidget;

private slots:
    void showAddWidget();
};

#endif // TEACHERWINDOW_H
