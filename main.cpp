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


    //Login Process
    loginWindow->show();
    if (loginWindow->exec() == QDialog::Rejected) {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow->loggedInUser.email();

    if (loginWindow->loggedInUser.email() == "teacher") {
        teacherWindow->show();
    } else {
        studentWindow->show();
    }

    return app->exec();
}
