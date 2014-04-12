#include "Question.h"

Question::Question(QWidget *parent)
: QWidget(parent) {
    vbox = new QVBoxLayout;
}

QGroupBox Question::createQuestion(QString qnsName, QString op1,
                                   QString op2, QString op3, QString op4) {

    // Question name
    *questionName = new QGroupBox(tr(qnsName));

    // Options
    *op1 = new QRadioButton(tr(op1));
    *op2 = new QRadioButton(tr(op2));
    *op3 = new QRadioButton(tr(op3));
    *op4 = new QRadioButton(tr(op4));

    // Set a vertical layout for the question and options
    vbox->addWidget(op1);
    vbox->addWidget(op2);
    vbox->addWidget(op3);
    vbox->addWidget(op4);
    //vbox->addStretch(1);
    questionName->setLayout(vbox);

    return questionName;

}

bool Question::isCorrect() {
    if(getSelectedOption() == answer) {
        return true;
    } else {
        return false;
    }
}

void Question::setAns(int ans) {
    answer = ans;
}

int Question::getAns() {
    return answer;
}

int Question::getSelectedOption() {
    if(op1->isChecked()) {
        return 1;
    } else if(op2->isChecked()) {
        return 2;
    } else if(op3->isChecked()) {
        return 3;
    } else if(op4->isChecked()) {
        return 4;
    } else {
        return 0;       // Student left question blank ):
    }
}

