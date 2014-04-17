#include "StudentWindow.h"

StudentWindow::StudentWindow(DatabaseLayer *db) : MainWindow(db, new StudentMainWidget())
{
    this->studentMainWidget = (StudentMainWidget *)mainWidget;
    this->lessonWidget = new StudentLessonWidget();
    this->testWidget = new TestWidget(db);

    connect(this->studentMainWidget, SIGNAL(selectedLesson(int)), this, SLOT(showLessonWidget(int)));
    connect(db, SIGNAL(newLessonCreated()), this, SLOT(newLessonCreated()));

    connect(this->lessonWidget, SIGNAL(prepared()), this->lessonWidget, SLOT(show()));
    connect(this->lessonWidget, SIGNAL(prepared()), this->studentMainWidget, SLOT(hide()));

    connect(this->lessonWidget, SIGNAL(transitLessons()), this->studentMainWidget, SLOT(show()));
    connect(this->lessonWidget, SIGNAL(logOut()), this, SLOT(logoff()));
    connect(this->lessonWidget, SIGNAL(transitLessons()), this->lessonWidget, SLOT(hide()));
    connect(this->lessonWidget, SIGNAL(logOut()), this->lessonWidget, SLOT(close()));

}

void StudentWindow::showLessonWidget(int i)
{
    LessonsDB *lessons = LessonsDBController::getDB();
    Lesson lesson = lessons->getLessons().at(i);
    this->lessonWidget->prepare(&lesson);
    
    connect(this->lessonWidget->menuWidget->lessonButton, SIGNAL(clicked()), this->lessonWidget, SLOT(transit()));
    connect(this->lessonWidget->menuWidget->logoutButton, SIGNAL(clicked()), this->lessonWidget, SLOT(exit()));

    connect(this->lessonWidget->menuWidget, SIGNAL(selectTest(bool)), this->testWidget, SLOT(prepare(bool)));
    connect(this->testWidget, SIGNAL(prepared()), this->testWidget, SLOT(show()));
    connect(this->testWidget, SIGNAL(prepared()), this->lessonWidget, SLOT(hide()));

    connect(this->testWidget, SIGNAL(transitLessonStudent()), this->testWidget, SLOT(hide()));
    connect(this->testWidget, SIGNAL(transitLessonStudent()), this->lessonWidget, SLOT(show()));
}

void StudentWindow::newLessonCreated()
{
     QMessageBox::information(0, "", "New Lesson Created");
     db->loadLessons();
     this->studentMainWidget->updateTable();
}
