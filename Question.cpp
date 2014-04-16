#include "Question.h"

Question::Question(QWidget *parent)
: QWidget(parent) {
    vbox = new QVBoxLayout();
    mainLayout = new QVBoxLayout();
}

QGroupBox *Question::setQuestion(QString name, QString op1,
                                   QString op2, QString op3,
                                   QString op4, int ans) {

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

