#include "TeacherWindow.h"


TeacherWindow::TeacherWindow(DatabaseLayer *db) : MainWindow(db, new TeacherMainWidget())
{
    this->teacherMainWidget = (TeacherMainWidget *)mainWidget;
    this->addWidget = new AddLessonWidget();
    this->editWidget = new LessonWidget();
    this->testWidget = new TestWidget();


    //Connections with Add New Lesson
    QObject::connect(this->teacherMainWidget->addNewButton, SIGNAL(clicked()), this->addWidget, SLOT(show()));
    QObject::connect(this->teacherMainWidget->addNewButton, SIGNAL(clicked()), this->teacherMainWidget, SLOT(hide()));
    QObject::connect(this->addWidget, SIGNAL(added()), this, SLOT(showMainWidget()));
    QObject::connect(this->addWidget, SIGNAL(added()), this->addWidget, SLOT(hide()));


    //Connections with edit button
    QObject::connect(this->teacherMainWidget, SIGNAL(edit()), this->editWidget, SLOT(prepare()));
    QObject::connect(this->teacherMainWidget, SIGNAL(edit()), this->teacherMainWidget, SLOT(hide()));
    QObject::connect(this->editWidget,SIGNAL(prepared()), this->editWidget,SLOT(show()));
    QObject::connect(this->editWidget, SIGNAL(saved()), this, SLOT(showMainWidget()));
    QObject::connect(this->editWidget, SIGNAL(saved()), this->editWidget, SLOT(hide()));

    //Logging out
    QObject::connect(this->teacherMainWidget->profileButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(this->teacherMainWidget->logOutButton, SIGNAL(clicked()), this, SLOT(save()));

    //Transiting to test
    QObject::connect(this->editWidget, SIGNAL(transitTest(bool)), this->testWidget, SLOT(prepare(bool)));
    QObject::connect(this->testWidget, SIGNAL(prepared()), this->testWidget, SLOT(show()));
    QObject::connect(this->editWidget, SIGNAL(hideEditWidget()), this->editWidget, SLOT(hide()));
    QObject::connect(this->testWidget, SIGNAL(transitLesson()), this->testWidget, SLOT(hide()));
    QObject::connect(this->testWidget, SIGNAL(transitLesson()), this->editWidget, SLOT(prepare()));

    //Transiting to edit Files/Images
    QObject::connect(this->editWidget, SIGNAL(transitEdit()), this->addWidget, SLOT(prepare()));
    QObject::connect(this->editWidget, SIGNAL(transitEdit()), this->editWidget, SLOT(hide()));
    QObject::connect(this->addWidget, SIGNAL(prepared()), this->addWidget, SLOT(show()));
    QObject::connect(this->addWidget, SIGNAL(prepared()), this->teacherMainWidget, SLOT(hide()));
    QObject::connect(this->addWidget, SIGNAL(saved()), this->editWidget, SLOT(prepare()));
    QObject::connect(this->addWidget, SIGNAL(saved()), this->addWidget, SLOT(hide()));

}

void TeacherWindow::save()
{
    db->saveLessons();
    this->teacherMainWidget->close();
}
