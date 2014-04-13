// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "LoginWindow.h"
#include "TeacherWindow.h"
#include "StudentWindow.h"
#include "LessonWidget.h"

#include "DatabaseLayer.h"


int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);

    /**
     *All Windows should be initialized here
     */

    DatabaseLayer databaseLayer;

    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();

    LoginWindow *loginWindow = new LoginWindow(&databaseLayer);
    TeacherWindow *teacherWindow = new TeacherWindow(&databaseLayer);
    StudentWindow *studentWindow = new StudentWindow(&databaseLayer);


    //Login Process
    loginWindow->show();
    if (loginWindow->exec() == QDialog::Rejected) {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow->loggedInUser.email();

    if (loginWindow->loggedInUser.userRole() == UserRoleTeacher) {
        teacherWindow->show();
    } else {
        studentWindow->show();
    }

    return app->exec();
}
