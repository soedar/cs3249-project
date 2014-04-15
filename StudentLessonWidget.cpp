#include "StudentLessonWidget.h"

StudentLessonWidget::StudentLessonWidget(Lesson *lesson)
{
    setGeometry(0,0,850,600);
    this->lesson = lesson;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(new QWidget);

    setLayout(mainLayout);

    qDebug() << "here" << lesson->getImageList();

    this->menuWidget = new MenuWidget(this, lesson);
    this->menuWidget->show();
}


void StudentLessonWidget::resizeEvent(QResizeEvent *event) 
{
    this->menuWidget->adjustSize();
}