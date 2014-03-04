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

    Project project;
    project.show();

    return app.exec();
}
