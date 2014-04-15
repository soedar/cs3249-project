#ifndef STUDENT_LESSONWIDGET_H
#define STUDENT_LESSONWIDGET_H

#include <QDialog>
#include <QHBoxLayout>
#include "Lesson.h"
#include "MenuWidget.h"

class StudentLessonWidget : public QDialog
{
public:
    StudentLessonWidget(Lesson *lesson);
    QWidget *pdfWidget;
    QWidget *imageWidget;

private:
    Lesson *lesson;
    MenuWidget *menuWidget;
    void resizeEvent(QResizeEvent *event);
};

#endif