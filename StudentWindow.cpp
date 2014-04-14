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

    StudentLessonWidget *lessonWidget = new StudentLessonWidget(&lesson);

    mainWidget->setParent(0);
    setCentralWidget(lessonWidget);
}