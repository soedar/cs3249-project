#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui>
#include "Question.h"
#include "TestsDBController.h"

class TestWidget : public QDialog
{
    Q_OBJECT
public:
    TestWidget();
    TestWidget(int i);   // need the lesson index in order to create

    void addQuestion(QString qnsName, QString op1,
                     QString op2, QString op3,
                     QString op4, int ans);
    void deleteQuestion(int i);
    void deleteAllQuestions();
    void saveTest();

private:
    void setLayout();

    TestsDB tests;
    QList<Question *> questionList;
    int index;

signals:
    // stick the back button here?
   // void transitLesson();

public slots:
  //  void saveAndTransitLesson();


};

#endif // TESTWIDGET_H
