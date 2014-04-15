// main.cpp

#include <QApplication>
#include "LessonsDBController.h"
#include "TestsDBController.h"
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

    /*
    TestsDBController *tdb = new TestsDBController();
    tdb->init();
    */

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
        databaseLayer.loadLessons();

        if (loggedInUser.userRole() == UserRoleTeacher) {
            chosenWindow = new TeacherWindow(&databaseLayer);
        } else {
            chosenWindow = new StudentWindow(&databaseLayer);
        }

        //chosenWindow->show();
        retValue = app->exec();
    } while (chosenWindow->didLoggedOff());

    return retValue;
}
