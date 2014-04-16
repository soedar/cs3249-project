#include "TestWidget.h"
#include "qdebug.h"


// The test widget contains a test with MCQ questions.
// A teacher can create/edit/delete a test, while
// a student can take the test.
TestWidget::TestWidget()
{
    tests = TestsDBController::getDB();
    // for testing
    //tests.forTesting(this);

    setGeometry(0,0,1000,600);
    setMouseTracking(true);

    questionList = QList<Question *>();
    vbox = new QVBoxLayout();
    vbox->setAlignment(Qt::AlignLeft);


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
    tests.forTesting(this);
    qDebug() << "Tests in system : " << tests.getTests().size() << "\n";
    questionList = tests.getTest(index);
    for(int i = 0; i < questionList.length(); i++)
    {
        vbox->addWidget(questionList[i]);
    }
    emit prepared();
}


