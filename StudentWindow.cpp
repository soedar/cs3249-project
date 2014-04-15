#include "StudentWindow.h"

StudentWindow::StudentWindow(DatabaseLayer *db) : MainWindow(db, new StudentMainWidget())
{
    this->studentMainWidget = (StudentMainWidget *)mainWidget;

    connect(this->studentMainWidget, SIGNAL(selectedLesson(int)), this, SLOT(showLessonWidget(int)));

}

void StudentWindow::showLessonWidget(int i)
{
    LessonsDB lessons = LessonsDBController::getDB();
    Lesson lesson = lessons.getLessons().at(i);

    lessonWidget = new StudentLessonWidget(&lesson);
    lessonWidget->show();
    studentMainWidget->hide();

    connect(lessonWidget->menuWidget->lessonButton, SIGNAL(clicked()), studentMainWidget, SLOT(show()));
    connect(lessonWidget->menuWidget->lessonButton, SIGNAL(clicked()), lessonWidget, SLOT(close()));
    connect(lessonWidget->menuWidget->logoutButton, SIGNAL(clicked()), lessonWidget, SLOT(close()));
    connect(lessonWidget->menuWidget->logoutButton, SIGNAL(clicked()), this, SLOT(logoff()));
}
