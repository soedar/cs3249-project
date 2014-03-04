// main.cpp

#include <QApplication>
#include <QtGui>
#include "LoginWindow.h"
#include "Project.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginWindow loginWindow;
    if (loginWindow.exec() == QDialog::Rejected) {
        return 0;
    }

    // loginWindow.loggedInUser now contain the logged in user
    qDebug() << loginWindow.loggedInUser.email();

    Project project;
    project.show();

    return app.exec();
}
