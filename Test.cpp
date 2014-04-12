#include "Test.h"

Test::Test() {

}

void Test::addQuestion(QString qns, QString op1, QString op2,
                       QString op3, QString op4, int ans) {

    Question question = new Question();
    question.createQuestion(qns, op1, op2, op3, op4);
    question.setAns(ans);
    questionList.append(question);
}

void Test::deleteTest() {

}

void Test::setLayout() {
    QVBoxLayout *vbox = new QVBoxLayout;

    for(int i = 0; i < questionList.length(); i++) {
        vbox->addWidget(questionList);
    }
    //  ->setLayout(vbox);

}
