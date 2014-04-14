#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui>
#include <Question.h>

class TestWidget : public QDialog
{
    Q_OBJECT
public:
    TestWidget();

    void addQuestion(QString qnsName, QString op1,
                     QString op2, QString op3,
                     QString op4, int ans);
    void deleteTest();

private:
    void setLayout();

    QList<Question *> questionList;

public slots:


};

#endif // TESTWIDGET_H
