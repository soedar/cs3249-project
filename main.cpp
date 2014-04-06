// main.cpp

#include <QApplication>
#include "Overseer.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Overseer overseer;

    //Login Process
    overseer.loginWindow.show();
    if (overseer.loginWindow.exec() == QDialog::Rejected)
    {
        return 0;
    }

    //loginWindow.loggedInUser now contain the logged in user
    qDebug() << overseer.loginWindow.loggedInUser.email();


    overseer.teacherWindow.show();


    return app.exec();
}
