#include "Question.h"

Question::Question()
{
    vbox = new QVBoxLayout();
    mainLayout = new QVBoxLayout();
}

QGroupBox *Question::setQuestion(QString name, QString op1,
                                   QString op2, QString op3,
                                   QString op4, int ans) {
    questionName = name;
    option1 = op1;
    option2 = op2;
    option3 = op3;
    option4 = op4;

    // Question name
    qnsName = new QGroupBox(name);

    // Options
    qnsOp1 = new QRadioButton(op1);
    qnsOp2 = new QRadioButton(op2);
    qnsOp3 = new QRadioButton(op3);
    qnsOp4 = new QRadioButton(op4);

    // Set a vertical layout for the question and options
    vbox->addWidget(qnsOp1);
    vbox->addWidget(qnsOp2);
    vbox->addWidget(qnsOp3);
    vbox->addWidget(qnsOp4);
    //vbox->addStretch(1);
    qnsName->setLayout(vbox);

    mainLayout->addWidget(qnsName);

    setLayout(mainLayout);

    answer = ans;

    return qnsName;

}

bool Question::isCorrect() {
    if(getSelectedOption() == answer) {
        return true;
    } else {
        return false;
    }
}

void Question::setQnsName(QString qns) {
    questionName = qns;
}

void Question::setOp1(QString op1) {
    option1 = op1;
}

void Question::setOp2(QString op2) {
    option2 = op2;
}

void Question::setOp3(QString op3) {
    option3 = op3;
}

void Question::setOp4(QString op4) {
    option4 = op4;
}

void Question::setAns(int ans) {
    answer = ans;
}

QString Question::getQnsName() {
    return questionName;
}

QString Question::getOp1() {
    return option1;
}

QString Question::getOp2() {
    return option2;
}

QString Question::getOp3() {
    return option3;
}

QString Question::getOp4() {
    return option4;
}

int Question::getAns() {
    return answer;
}

int Question::getSelectedOption() {
    if(qnsOp1->isChecked()) {
        return 1;
    } else if(qnsOp2->isChecked()) {
        return 2;
    } else if(qnsOp3->isChecked()) {
        return 3;
    } else if(qnsOp4->isChecked()) {
        return 4;
    } else {
        return 0;       // Student left question blank ):
    }
}

