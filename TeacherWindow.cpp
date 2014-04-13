#include "TeacherWindow.h"


TeacherWindow::TeacherWindow(DatabaseLayer *db) : MainWindow(db, new TeacherMainWidget())
{
    this->teacherMainWidget = (TeacherMainWidget *)mainWidget;
}

void TeacherWindow::toggleAddWidget()
{
    addWidget = new AddLessonWidget();
    QObject::connect(addWidget->uploadBtn, SIGNAL(clicked()), this, SLOT(toggleMainWidget()));
    mainWidget->setParent(0);
    setCentralWidget(addWidget);
}
