#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include "TeacherMainWidget.h"
#include "AddLessonWidget.h"
#include "MainWindow.h"
#include "DatabaseLayer.h"
#include "LessonWidget.h"
#include "TestWidget.h"

class TeacherWindow : public MainWindow
{
    Q_OBJECT
public:
    TeacherWindow(DatabaseLayer *db, User loggedInUser);


private:
    TeacherMainWidget *teacherMainWidget;
    AddLessonWidget *addWidget;
    LessonWidget *editWidget;
    TestWidget *testWidget;

private slots:

    void save();
};

#endif // TEACHERWINDOW_H
