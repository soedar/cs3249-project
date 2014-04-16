#include "TestWidget.h"
#include "qdebug.h"


// The test widget contains a test with MCQ questions.
// A teacher can create/edit/delete a test, while
// a student can take the test.
TestWidget::TestWidget()
{
    tests = TestsDBController::getDB();

    setGeometry(0,0,1000,600);

    questionList = QList<Question *>();
    mainLayout = new QVBoxLayout();
    menu = new QGroupBox();

    testTable = new QTableWidget;
    testTable->setRowCount(0);
    testTable->setColumnCount(1);

    QStringList testTableHeader;
    testTableHeader << "Questions";
    testTable->setHorizontalHeaderLabels(testTableHeader);

    mainLayout->addWidget(menu);
    mainLayout->addWidget(testTable);
    setLayout(mainLayout);
}

void TestWidget::addQuestion(QString qnsName, QString op1, QString op2,
                       QString op3, QString op4, int ans) {

    Question *question = new Question(this);
    question->setQuestion(qnsName, op1, op2, op3, op4, ans);
    questionList.append(question);

    qDebug("Successfully added qns");
}

void TestWidget::deleteQuestion(int i) {
    questionList.removeAt(i);
}

// TODO: add confirmation dialog if there's time
void TestWidget::deleteAllQuestions() {
    // confirmation dialog here


    // replace the list of questions with an empty one
    questionList = QList<Question *>();

    // need to redraw to show blank window?

}

void TestWidget::saveTest() {
    tests.saveTest(index, questionList);
}

QPair<int, int> TestWidget::getMarks() {
    return qMakePair(marks, questionList.length());
}

void TestWidget::createMenu() {

    hbox = new QHBoxLayout;

    back = new QPushButton(tr("Back to lessons"));
    connect(back, SIGNAL(clicked()), this, SLOT(saveAndTransitLesson()));
    hbox->addWidget(back);

    marksText = new QLabel(this);
    marksText->setText(QString("Marks from last attempt: %1/%2")
                       .arg(marks).arg(questionList.length()));
    hbox->addWidget(marksText);

    menu->setLayout(hbox);
}


// PUBLIC SLOTS

void TestWidget::saveAndTransitLesson()
{
    saveTest();
    int len = questionList.length();
    for (int i=0; i<len; i++)
    {
        Question *tempQn = questionList.takeLast();
        mainLayout->removeWidget(tempQn);
    }

    // remove everything from the table
    for(int i = testTable->rowCount()-1; i >= 0; i--) {
        testTable->removeRow(i);
    }

    emit transitLesson();
}

void TestWidget::prepare(bool teacher)
{
    index = LessonsDBController::getIndex();
    tests = TestsDBController::getDB();
    isTeacher = teacher;

    int width;

    // REMOVE ! once testing is done!
    if(!isTeacher) {
        qDebug("student");
        width = 1000;
    } else {
        qDebug("teacher");
        width = 800;
    }
    testTable->setColumnWidth(0, width);

    // get marks from db before calling create menu


    createMenu();

    // for testing only
    tests.forTesting(this);

    qDebug() << "Tests in system : " << tests.getTests().size() << "\n";
    questionList = tests.getTest(index);
    for(int i = 0; i < questionList.length(); i++) {
        testTable->insertRow(testTable->rowCount());
        testTable->setRowHeight(testTable->rowCount()-1, 200);
        testTable->setCellWidget(testTable->rowCount()-1, 0,
                                questionList[i]);
    }

    if(!isTeacher) {
        qDebug("student");
    } else {
        qDebug("teacher");

        // create submit button for student
        submitButton = new QPushButton(tr("Submit"));
        submitButton->setEnabled(true);
        connect(submitButton, SIGNAL(clicked()), this, SLOT(submitTest()));

        testTable->insertRow(testTable->rowCount());
        testTable->setCellWidget(testTable->rowCount()-1, 0,
                                    submitButton);
    }

    emit prepared();
}

// for student
void TestWidget::submitTest() {
    marks = 0;

    testTable->removeRow(testTable->rowCount()-1);
    testTable->insertColumn(1);
    testTable->setColumnWidth(1, 141);
    testTableHeader << "Questions" << "Results";
    testTable->setHorizontalHeaderLabels(testTableHeader);

    for(int i = 0; i < testTable->rowCount(); i++) {
        QLabel *qnsResult = new QLabel(this);
        qnsResult->setAlignment(Qt::AlignCenter);

        if(questionList[i]->isCorrect()) {
            qnsResult->setText("CORRECT!");
            marks++;
        } else {
            int ans = questionList[i]->getAns();
            qnsResult->setText(QString("WRONG.\nCorrect answer: %1.").arg(ans));
        }

        testTable->setCellWidget(i, 1, qnsResult);
    }

    marksText->setText(QString("Marks from last attempt: %1/%2")
                       .arg(marks).arg(questionList.length()));
}
