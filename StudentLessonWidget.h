#ifndef STUDENT_LESSONWIDGET_H
#define STUDENT_LESSONWIDGET_H

#include <QDialog>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include "Lesson.h"
#include "MenuWidget.h"

class StudentLessonWidget : public QDialog
{
public:
    StudentLessonWidget(Lesson *lesson);
    QWidget *pdfWidget;
    QWidget *imageWidget;
    MenuWidget *menuWidget;
    QTextEdit *textEditWidget;

private:
    Lesson *lesson;
    void resizeEvent(QResizeEvent *event);
};

#endif