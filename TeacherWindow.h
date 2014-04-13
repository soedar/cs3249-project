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
    TeacherMainWidget *mainWidget;
    AddLessonWidget *addWidget;

private slots:
void toggleAddWidget();
void toggleMainWidget();
};

#endif // TEACHERWINDOW_H
