#include "TeacherWindow.h"


TeacherWindow::TeacherWindow(DatabaseLayer *db) : MainWindow(db, new TeacherMainWidget())
{
    this->teacherMainWidget = (TeacherMainWidget *)mainWidget;

    QObject::connect(teacherMainWidget->addNewButton, SIGNAL(clicked()), this, SLOT(showAddWidget()));
}

void TeacherWindow::showAddWidget()
{
    addWidget = new AddLessonWidget();
    QObject::connect(addWidget->uploadBtn, SIGNAL(clicked()), this, SLOT(showMainWidget()));
    mainWidget->setParent(0);
    setCentralWidget(addWidget);
}
