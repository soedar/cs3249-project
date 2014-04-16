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
    TestWidget();

    void addQuestion(QString qnsName, QString op1,
                     QString op2, QString op3,
                     QString op4, int ans);
    void deleteQuestion(int i);
    void deleteAllQuestions();
    void saveTest();
    QPair<int, int> getMarks();

private:

    TestsDB tests;
    QList<Question *> questionList;
    QVBoxLayout *mainLayout;
    QGroupBox *menu;
    QHBoxLayout *hbox;

    // student stuff
    QTableWidget *testTable;
    QStringList testTableHeader;

    QPushButton *back;
    QPushButton *submitButton;

    void createMenu();

    QLabel *marksText;
    bool isTeacher;
    int index;
    int marks;

signals:
    void transitLesson();
    void transitLessonStudent();
    void prepared();

public slots:
    void saveAndTransitLesson();
    void prepare(bool teacher);


    void submitTest();

};

#endif // TESTWIDGET_H
