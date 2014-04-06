#include "Overseer.h"

Overseer::Overseer()
{
    ldb = new LessonsDBController();
    ldb->init();
    loginWindow = LoginWindow();
    teacherWindow = TeacherWindow();
    addLessonWindow = AddLessonWindow();
    project = Project();
    QPushButton *button = teacherWindow.getAddButton();

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(openAddLessonWindow()));
   // QObject::connect(teacherWindow.getAddButton(), SIGNAL(clicked()),this, SLOT(openAddLessonWindow()));
    QObject::connect(addLessonWindow.getBtn(), SIGNAL(clicked()),this, SLOT(closeAddLessonWindow()));
}

void Overseer::openAddLessonWindow()
{
    teacherWindow.hide();
    addLessonWindow.show();
}

void Overseer::closeAddLessonWindow()
{
    teacherWindow.show();
    addLessonWindow.hide();
}
