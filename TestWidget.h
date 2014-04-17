#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui>
#include "Question.h"
#include "TestsDBController.h"
#include "LessonsDBController.h"
#include "DatabaseLayer.h"
#include "MarksDB.h"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(DatabaseLayer *db, QString email);
    QPair<int, int> getMarks();

private:

    DatabaseLayer *db;
    QString email;
    TestsDB *tests;
    QList<QuestionItem *> questionList;
    QGroupBox *menuStudent;
    QGroupBox *menuTeacher;
    QVBoxLayout *vboxStudent;
    QVBoxLayout *vboxTeacher;

    QTableWidget *testTable;
    QStringList testTableHeader;

    QPushButton *backButton;

    // teacher stuff
    QPushButton *saveButton;
    QPushButton *deleteTestButton;
    QPushButton *addQnsButton;
    QPushButton *deleteQnsButton;

    // student stuff
    QPushButton *submitButton;

    void createMenu();

    QLabel *marksText;
    bool isTeacher;
    int index;
    int marks;
    int numSelected;

    void setMainLayout();
signals:
    void transitLesson();
    void transitLessonStudent();
    void prepared();

public slots:
    void backToLesson();
    void prepare(bool teacher);
    void toggle(bool checked);

    void addQuestion();
    void deleteSelectedQns();
    void deleteTest();
    void saveTest();
    void submitTest();

};

#endif // TESTWIDGET_H
