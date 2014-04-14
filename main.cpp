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

<<<<<<< HEAD
    LessonsDBController *ldb = new LessonsDBController();
    ldb->init();

    TestsDBController *tdb = new TestsDBController();
    tdb->init();

=======
>>>>>>> origin/refactor
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
