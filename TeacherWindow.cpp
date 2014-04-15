#include "TeacherWindow.h"


TeacherWindow::TeacherWindow(DatabaseLayer *db) : MainWindow(db, new TeacherMainWidget())
{
    this->teacherMainWidget = (TeacherMainWidget *)mainWidget;
    this->editWidget = new LessonWidget();
    this->testWidget = new TestWidget();

    QObject::connect(teacherMainWidget->addNewButton, SIGNAL(clicked()), this, SLOT(showAddWidget()));
    QObject::connect(teacherMainWidget, SIGNAL(edit()), this->editWidget, SLOT(prepare()));
    QObject::connect(this->editWidget,SIGNAL(prepared()), this->editWidget,SLOT(show()));
    QObject::connect(this->editWidget, SIGNAL(saved()), teacherMainWidget, SLOT(updateTable()));
    QObject::connect(this->editWidget, SIGNAL(saved()), this->editWidget, SLOT(hide()));
    QObject::connect(teacherMainWidget->profileButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(teacherMainWidget->logOutButton, SIGNAL(clicked()), this, SLOT(save()));

    QObject::connect(this->editWidget, SIGNAL(transit()), this->testWidget, SLOT(show()));
    QObject::connect(this->editWidget, SIGNAL(transit()), this->editWidget, SLOT(hide()));
}

void TeacherWindow::showAddWidget()
{
    addWidget = new AddLessonWidget();
    QObject::connect(addWidget->uploadBtn, SIGNAL(clicked()), this, SLOT(showMainWidget()));
    mainWidget->setParent(0);
    setCentralWidget(addWidget);
}

void TeacherWindow::save()
{
    db->saveLessons();
}
