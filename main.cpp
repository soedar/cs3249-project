// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "LoginWindow.h"
#include "AddLessonWindow.h"
#include "TeacherWindow.h"
#include "StudentWindow.h"
#include "Project.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);

    /**
     *All Windows should be initialized here
     */

    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();
    LoginWindow *loginWindow = new LoginWindow();
    AddLessonWindow *addLessonWindow = new AddLessonWindow();
    TeacherWindow *teacherWindow = new TeacherWindow();
    StudentWindow *studentWindow = new StudentWindow();
    Project *project = new Project();

    /**
     * Put all the connections here. For some reason having an overseer doesnt work so.. yeah
     * so just put them here
     */

    QObject::connect(teacherWindow->addNewButton,SIGNAL(clicked()),teacherWindow,SLOT(hide()));
    QObject::connect(teacherWindow->addNewButton,SIGNAL(clicked()),addLessonWindow,SLOT(show()));

    QObject::connect(addLessonWindow->uploadBtn,SIGNAL(clicked()),teacherWindow,SLOT(updateTable()));
    QObject::connect(addLessonWindow->uploadBtn,SIGNAL(clicked()),teacherWindow,SLOT(show()));
    QObject::connect(addLessonWindow->uploadBtn,SIGNAL(clicked()),addLessonWindow,SLOT(hide()));

    /*
     *
     * This part need to find a way to return user to login window and log in again
    QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),teacherWindow,SLOT(hide()));
    QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),loginWindow,SLOT(show()));

    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),studentWindow,SLOT(hide()));
    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),loginWindow,SLOT(show()));
    */

    QObject::connect(teacherWindow->logOutButton,SIGNAL(clicked()),app,SLOT(closeAllWindows()));
    QObject::connect(studentWindow->logOutButton,SIGNAL(clicked()),app,SLOT(closeAllWindows()));


    //Login Process

    loginWindow->show();
    if (loginWindow->exec() == QDialog::Rejected)
    {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow->loggedInUser.email();

    if (loginWindow->loggedInUser.email() == "teacher")
    {
        teacherWindow->show();
    }
    else
    {
        studentWindow->show();
    }
    //project.show();

    return app->exec();
}
