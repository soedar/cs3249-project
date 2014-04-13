#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "TeacherMainWidget.h"
#include "AddLessonWidget.h"
#include "DatabaseLayer.h"

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    TeacherWindow(DatabaseLayer *db);

private:
    TeacherMainWidget *mainWidget;
    AddLessonWidget *addWidget;
    DatabaseLayer *db;

private slots:
void toggleAddWidget();
void toggleMainWidget();
};

#endif // TEACHERWINDOW_H
