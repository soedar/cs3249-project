#include "TestWidget.h"


// The test widget contains a test with MCQ questions.
// A teacher can create/edit/delete a test, while
// a student can take the test.
TestWidget::TestWidget()
{
    setGeometry(0,0,1000,600);
    setMouseTracking(true);

}

void TestWidget::addQuestion(QString qnsName, QString op1, QString op2,
                       QString op3, QString op4, int ans) {

    Question *question = new Question(this);
    question->createQuestion(qnsName, op1, op2, op3, op4);
    question->setAns(ans);
    questionList.append(question);
}

void TestWidget::deleteTest() {

}

void TestWidget::setLayout() {
    QWidget *window = new QWidget;

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setAlignment(Qt::AlignLeft);
    for(int i = 0; i < questionList.length(); i++) {
        vbox->addWidget(questionList[i]);
    }

    window->setLayout(vbox);
    window->show();

}
