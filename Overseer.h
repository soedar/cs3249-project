#ifndef OVERSEER_H
#define OVERSEER_H

#include <QObject>
#include <LessonsDBController.h>
#include <LoginWindow.h>
#include <TeacherWindow.h>
#include <AddLessonWindow.h>
#include <Project.h>

class Overseer
{
    Q_OBJECT
public:
    Overseer();

    LessonsDBController *ldb;
    LoginWindow loginWindow;
    TeacherWindow teacherWindow;
    AddLessonWindow addLessonWindow;
    Project project;

public slots:
    void openAddLessonWindow();
    void closeAddLessonWindow();
};

#endif // OVERSEER_H
