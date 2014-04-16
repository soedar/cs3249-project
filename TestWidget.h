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

    void deleteQuestion(int i);
    QPair<int, int> getMarks();

private:

    TestsDB tests;
    QList<Question *> questionList;
    QVBoxLayout *mainLayout;
    QGroupBox *menu;
    QHBoxLayout *hbox;

    QTableWidget *testTable;
    QStringList testTableHeader;

    QPushButton *backButton;

    // teacher stuff
    QPushButton *saveButton;
    QPushButton *deleteAllButton;
    QPushButton *addQnsButton;

    // student stuff
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
    void backToLesson();
    void prepare(bool teacher);

    void addQuestion();
    void deleteAllQuestions();
    void saveTest();
    void submitTest();

};

#endif // TESTWIDGET_H
