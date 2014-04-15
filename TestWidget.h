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
    TestWidget(QString name);   // need the lesson name in order to create

    void addQuestion(QString qnsName, QString op1,
                     QString op2, QString op3,
                     QString op4, int ans);
    void saveTest();
    void deleteTest();

private:
    void setLayout();

    TestsDB tests;
    QList<Question *> questionList;
    QString lessonName;

signals:
    // stick the back button here?

public slots:


};

#endif // TESTWIDGET_H
