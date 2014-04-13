// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "LoginWindow.h"
#include "TeacherWindow.h"
#include "StudentWindow.h"

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


    MainWindow *chosenWindow;
    int retValue;
    do {
        LoginWindow *loginWindow = new LoginWindow(&databaseLayer);

        //Login Process
        loginWindow->show();
        if (loginWindow->exec() == QDialog::Rejected) {
            return 0;
        }

        User loggedInUser = loginWindow->loggedInUser;

        TeacherWindow *teacherWindow = new TeacherWindow(&databaseLayer);
        StudentWindow *studentWindow = new StudentWindow(&databaseLayer);

        if (loggedInUser.userRole() == UserRoleTeacher) {
            chosenWindow = teacherWindow;
        } else {
            chosenWindow = studentWindow;
        }

        chosenWindow->show();
        retValue = app->exec();
    } while (chosenWindow->didLoggedOff());

    return retValue;
}
