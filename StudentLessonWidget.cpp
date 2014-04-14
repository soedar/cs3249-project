#include "StudentLessonWidget.h"

StudentLessonWidget::StudentLessonWidget(Lesson *lesson)
{
    this->lesson = lesson;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(new QWidget);

    setLayout(mainLayout);

    qDebug() << lesson->getImageList();
}