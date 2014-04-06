// main.cpp

#include <QApplication>
#include <QtGui>
#include "LoginWindow.h"
#include "TeacherWindow.h"
#include "AddLessonWindow.h"
#include "Project.h"
#include "LessonsDBController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   /* LoginWindow loginWindow;
    if (loginWindow.exec() == QDialog::Rejected) {
        return 0;
    }

    // loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow.loggedInUser.email();*/

    //TeacherWindow teacherWindow;

    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();
    AddLessonWindow wind;


    Project project;
    wind.show();

    return app.exec();
}
