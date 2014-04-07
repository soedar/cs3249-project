// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "LoginWindow.h"
#include "AddLessonWindow.h"
#include "TeacherWindow.h"
#include "Project.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /**
     *All Windows should be initialized here
     */

    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();
    LoginWindow *loginWindow = new LoginWindow();
    AddLessonWindow *addLessonWindow = new AddLessonWindow();
    TeacherWindow *teacherWindow = new TeacherWindow();
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



    //Login Process

    loginWindow->show();
    if (loginWindow->exec() == QDialog::Rejected)
    {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow->loggedInUser.email();

    teacherWindow->show();
    //project.show();

    return app.exec();
}
