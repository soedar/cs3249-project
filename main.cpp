// main.cpp

#include <QApplication>
#include "Project.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Project project;
    project.show();
    return app.exec();
}
