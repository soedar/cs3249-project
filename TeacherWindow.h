#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "TeacherMainWidget.h"
#include "AddLessonWidget.h"

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    TeacherWindow();

private:
    TeacherMainWidget *mainWidget;
    AddLessonWidget *addWidget;

private slots:
void toggleAddWidget();
void toggleMainWidget();
};

#endif // TEACHERWINDOW_H
