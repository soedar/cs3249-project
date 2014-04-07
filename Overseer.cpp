#include "Overseer.h"

Overseer::Overseer()
{
    ldb = new LessonsDBController();
    ldb->init();
    loginWindow;
    teacherWindow = new TeacherWindow();
    addLessonWindow = new AddLessonWindow();
    project = new Project();
    //QPushButton *button = teacherWindow->getAddButton();

    //QObject::connect(button, SIGNAL(clicked()), this, SLOT(openAddLessonWindow()));
    //QObject::connect(addLessonWindow->getBtn(),SIGNAL(clicked()), this ,SLOT(closeAddLessonWindow()));
   // QObject::connect(teacherWindow.getAddButton(), SIGNAL(clicked()),this, SLOT(openAddLessonWindow()));
   // QObject::connect(addLessonWindow.getBtn(), SIGNAL(clicked()),this, SLOT(closeAddLessonWindow()));
}

void Overseer::openAddLessonWindow()
{
    teacherWindow->setVisible(false);
    addLessonWindow->setVisible(true);
}

void Overseer::closeAddLessonWindow()
{
    teacherWindow->setVisible(true);
    addLessonWindow->setVisible(false);
    teacherWindow->populateTableData();
}
