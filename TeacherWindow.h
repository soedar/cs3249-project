#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include "TeacherMainWidget.h"
#include "AddLessonWidget.h"
#include "MainWindow.h"
#include "DatabaseLayer.h"
#include "LessonWidget.h"

class TeacherWindow : public MainWindow
{
    Q_OBJECT
public:
    TeacherWindow(DatabaseLayer *db);

private:
    TeacherMainWidget *teacherMainWidget;
    AddLessonWidget *addWidget;
    LessonWidget *editWidget;

private slots:
    void showAddWidget();
    void save();
};

#endif // TEACHERWINDOW_H
