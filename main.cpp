// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "LoginWindow.h"
#include "TeacherWindow.h"
#include "StudentWindow.h"
#include "Project.h"
#include "LessonWidget.h"

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);

    /**
     *All Windows should be initialized here
     */

    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();
    LoginWindow *loginWindow = new LoginWindow();
    TeacherWindow *teacherWindow = new TeacherWindow();
    StudentWindow *studentWindow = new StudentWindow();
    Project *project = new Project();
    LessonWidget *widget = new LessonWidget();


    /**
     * Put all the connections here. For some reason having an overseer doesnt work so.. yeah
     * so just put them here
     */

    //QObject::connect(teacherWindow->addNewButton,SIGNAL(clicked()),teacherWindow,SLOT(hide()));
    //QObject::connect(teacherWindow->addNewButton,SIGNAL(clicked()),addLessonWindow,SLOT(show()));

    //QObject::connect(addLessonWindow->uploadBtn,SIGNAL(clicked()),teacherWindow,SLOT(updateTable()));
    //QObject::connect(addLessonWindow->uploadBtn,SIGNAL(clicked()),teacherWindow,SLOT(show()));


    //QObject::connect(teacherWindow, SIGNAL(edit()), widget, SLOT(prepare()));
    QObject::connect(widget,SIGNAL(prepared()),widget,SLOT(show()));
    //QObject::connect(widget,SIGNAL(prepared()),teacherWindow,SLOT(hide()));

    //QObject::connect(widget,SIGNAL(saved()),teacherWindow,SLOT(updateTable()));
    //QObject::connect(widget,SIGNAL(saved()),teacherWindow,SLOT(show()));
    QObject::connect(widget,SIGNAL(saved()),widget,SLOT(hide()));

    /*
     *
     * This part need to find a way to return user to login window and log in again
     *
    QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),teacherWindow,SLOT(hide()));
    QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),loginWindow,SLOT(show()));

    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),studentWindow,SLOT(hide()));
    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),loginWindow,SLOT(show()));
    */

    //QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),app,SLOT(closeAllWindows()));
    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),app,SLOT(closeAllWindows()));


    //Login Process

    teacherWindow->show();
/*
    loginWindow->show();
    if (loginWindow->exec() == QDialog::Rejected)
    {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow->loggedInUser.email();

    //widget->show();

    if (loginWindow->loggedInUser.email() == "teacher")
    {
        teacherWindow->show();
    }
    else
    {
        studentWindow->show();
    }
    //project.show();
    */

    return app->exec();

}
