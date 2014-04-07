#ifndef OVERSEER_H
#define OVERSEER_H

#include <LoginWindow.h>
#include <TeacherWindow.h>
#include <AddLessonWindow.h>
#include <Project.h>

class Overseer
{

public:
    Overseer();
    void openAddLessonWindow();
    void closeAddLessonWindow();
    LessonsDBController *ldb;
    LoginWindow *loginWindow;
    TeacherWindow *teacherWindow;
    AddLessonWindow *addLessonWindow;
    Project *project;

};

#endif // OVERSEER_H
