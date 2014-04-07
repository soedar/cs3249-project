// main.cpp

#include <QApplication>
#include "Overseer.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Overseer *overseer = new Overseer();


    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();
    LoginWindow *loginWindow = new LoginWindow();
    AddLessonWindow *addLessonWindow = new AddLessonWindow();
    TeacherWindow *teacherWindow = new TeacherWindow();
    Project *project = new Project();



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
