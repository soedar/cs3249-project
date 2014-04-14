#include "TeacherWindow.h"


TeacherWindow::TeacherWindow(DatabaseLayer *db) : MainWindow(db, new TeacherMainWidget())
{
    this->teacherMainWidget = (TeacherMainWidget *)mainWidget;
    this->editWidget = new LessonWidget();

    QObject::connect(teacherMainWidget->addNewButton, SIGNAL(clicked()), this, SLOT(showAddWidget()));
    QObject::connect(teacherMainWidget, SIGNAL(edit()), this->editWidget, SLOT(prepare()));
    QObject::connect(this->editWidget,SIGNAL(prepared()), this->editWidget,SLOT(show()));
}

void TeacherWindow::showAddWidget()
{
    addWidget = new AddLessonWidget();
    QObject::connect(addWidget->uploadBtn, SIGNAL(clicked()), this, SLOT(showMainWidget()));
    mainWidget->setParent(0);
    setCentralWidget(addWidget);
}
