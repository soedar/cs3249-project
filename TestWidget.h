#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui>
#include "Question.h"
#include "TestsDBController.h"
#include "LessonsDBController.h"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(bool teacher);

    void addQuestion(QString qnsName, QString op1,
                     QString op2, QString op3,
                     QString op4, int ans);
    void deleteQuestion(int i);
    void deleteAllQuestions();
    void saveTest();

private:

    TestsDB tests;
    QList<Question *> questionList;
    QVBoxLayout *vbox;

    // student stuff
    QTableWidget *testTable;
    QStringList testTableHeader;
    QPushButton *submitButton;


    bool isTeacher;
    int index;

signals:
    void transitLesson();
    void prepared();

public slots:
    void saveAndTransitLesson();
    void prepare();
    void submitTest();

};

#endif // TESTWIDGET_H
