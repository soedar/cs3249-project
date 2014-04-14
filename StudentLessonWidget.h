#ifndef STUDENT_LESSONWIDGET_H
#define STUDENT_LESSONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "Lesson.h"

class StudentLessonWidget : public QWidget
{
public:
    StudentLessonWidget(Lesson *lesson);
    QWidget *pdfWidget;
    QWidget *imageWidget;

private:
    Lesson *lesson;
};

#endif