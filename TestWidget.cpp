#include "TestWidget.h"
#include "qdebug.h"


// The test widget contains a test with MCQ questions.
// A teacher can create/edit/delete a test, while
// a student can take the test.
TestWidget::TestWidget(bool teacher)
{
    isTeacher = teacher;
    tests = TestsDBController::getDB();

    setGeometry(0,0,1000,600);
    setMouseTracking(true);

    questionList = QList<Question *>();
    vbox = new QVBoxLayout();

    int width;

    // REMOVE ! once testing is done!
    if(!isTeacher) {
        qDebug("student");
        width = 1000;
    } else {
        qDebug("teacher");
        width = 800;
    }

    testTable = new QTableWidget;
    testTable->setRowCount(0);
    testTable->setColumnCount(1);
    testTable->setColumnWidth(0, width);

    QStringList testTableHeader;
    testTableHeader << "Questions";
    testTable->setHorizontalHeaderLabels(testTableHeader);

    vbox->addWidget(testTable);
    setLayout(vbox);
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

void TestWidget::saveAndTransitLesson()
{
    saveTest();
    int len = questionList.length();
    for (int i=0; i<len; i++)
    {
        Question *tempQn = questionList.takeLast();
        vbox->removeWidget(tempQn);
    }
    emit transitLesson();
}

void TestWidget::saveTest() {
    tests.saveTest(index, questionList);
}

void TestWidget::prepare()
{
    index = LessonsDBController::getIndex();
    tests = TestsDBController::getDB();

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

        //submitTest();
    }

    emit prepared();
}

// for student
void TestWidget::submitTest() {
    testTable->removeRow(testTable->rowCount()-1);
    testTable->insertColumn(1);
    testTable->setColumnWidth(1, 141);
    testTableHeader << "Questions" << "Results";
    testTable->setHorizontalHeaderLabels(testTableHeader);

    for(int i = 0; i < testTable->rowCount(); i++) {
        QLabel *qnsResult = new QLabel(this);
        qnsResult->setAlignment(Qt::AlignCenter);


//        // why the heck is the answer to the last qns so weird
//        // when this function is called through signal/slot??
//        for(int j = 0; j < questionList.length(); j++) {
//            int test = questionList[j]->getAns();
//            qDebug("qns %d ans is %d", j+1, test);
//        }


        if(questionList[i]->isCorrect()) {
            qnsResult->setText("CORRECT!");
            qDebug("correct\n");
        } else {
            int ans = questionList[i]->getAns();
            qnsResult->setText(QString("WRONG.\nCorrect answer: %1.").arg(ans));
            qDebug("Wrong.\nCorrect answer is %d.\n", ans);
        }

        testTable->setCellWidget(i, 1, qnsResult);
        qDebug("set widget");
    }
}
