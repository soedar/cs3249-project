#include "Question.h"

Question::Question()
{
    question = new QuestionItem();
    //Student Layout
    vboxStudent = new QVBoxLayout();
    mainLayoutStudent = new QVBoxLayout();

    qnsName = new QGroupBox();
    qnsOp1 = new QRadioButton();
    qnsOp2 = new QRadioButton();
    qnsOp3 = new QRadioButton();
    qnsOp4 = new QRadioButton();

    vboxStudent->addWidget(qnsOp1);
    vboxStudent->addWidget(qnsOp2);
    vboxStudent->addWidget(qnsOp3);
    vboxStudent->addWidget(qnsOp4);

    qnsName->setLayout(vboxStudent);

    mainLayoutStudent->addWidget(qnsName);


    //Teacher Layout
    gridTeacher = new QGridLayout();
    mainLayoutTeacher = new QVBoxLayout();
    qnsEdit = new QGroupBox();

    editAns = new QComboBox();
    QStringList numbers;
    numbers << "0" << "1" << "2" << "3" << "4";
    editAns->addItems(numbers);

    editName = new QLineEdit();
    editOp1 = new QLineEdit();
    editOp2 = new QLineEdit();
    editOp3 = new QLineEdit();
    editOp4 = new QLineEdit();

    QLabel *qnsNameLabel = new QLabel;
    qnsNameLabel->setText("Question:");

    QLabel *op1Label = new QLabel;
    op1Label->setText("Option 1:");

    QLabel *op2Label = new QLabel;
    op2Label->setText("Option 2:");

    QLabel *op3Label = new QLabel;
    op3Label->setText("Option 3:");

    QLabel *op4Label = new QLabel;
    op4Label->setText("Option 4:");

    QLabel *ansLabel = new QLabel;
    ansLabel->setText("Answer:");

    gridTeacher->addWidget(qnsNameLabel,0,0);
    gridTeacher->addWidget(op1Label,1,0);
    gridTeacher->addWidget(op2Label,2,0);
    gridTeacher->addWidget(op3Label,3,0);
    gridTeacher->addWidget(op4Label,4,0);
    gridTeacher->addWidget(ansLabel,5,0);
    gridTeacher->addWidget(editName,0,1);
    gridTeacher->addWidget(editOp1,1,1);
    gridTeacher->addWidget(editOp2,2,1);
    gridTeacher->addWidget(editOp3,3,1);
    gridTeacher->addWidget(editOp4,4,1);
    gridTeacher->addWidget(editAns,5,1);

    qnsEdit->setLayout(gridTeacher);
    mainLayoutTeacher->addWidget(qnsEdit);
}


void Question::setQuestion(QString name, QString op1,
                                   QString op2, QString op3,
                                   QString op4, int ans)
{
    question = new QuestionItem();
    setQnsName(name);
    setOp1(op1);
    setOp2(op2);
    setOp3(op3);
    setOp4(op4);
    setAns(ans);
}

void Question::setQuestion(QuestionItem *item)
{
    question = new QuestionItem();
    setQuestion(item->getQnName(),item->getOp1(),item->getOp2(),
                item->getOp3(),item->getOp4(),item->getAns());
}

void Question::saveQuestion()
{
    question->setAns(editAns->currentIndex());
    question->setOp1(editOp1->text());
    question->setOp2(editOp2->text());
    question->setOp3(editOp3->text());
    question->setOp4(editOp4->text());
    question->setQnName(editName->text());
}

QuestionItem* Question::getQuestion()
{
    return question;
}

void Question::setLayoutStudent()
{
    setLayout(mainLayoutStudent);
}

void Question::setLayoutTeacher()
{
    setLayout(mainLayoutTeacher);
}

bool Question::isCorrect()
{
    if(getSelectedOption() == question->getAns())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Question::setQnsName(QString qns)
{
    question->setQnName(qns);
    qnsName->setTitle(qns);
    editName->setText(qns);
}

void Question::setOp1(QString op1)
{
    question->setOp1(op1);
    qnsOp1->setText(op1);
    editOp1->setText(op1);
}

void Question::setOp2(QString op2)
{
    question->setOp2(op2);
    qnsOp2->setText(op2);
    editOp2->setText(op2);
}

void Question::setOp3(QString op3)
{
    question->setOp1(op3);
    qnsOp3->setText(op3);
    editOp3->setText(op3);
}

void Question::setOp4(QString op4)
{
    question->setOp1(op4);
    qnsOp4->setText(op4);
    editOp4->setText(op4);
}

void Question::setAns(int ans)
{
    question->setAns(ans);
    editAns->setCurrentIndex(ans);
}

QString Question::getQnsName()
{
    return question->getQnName();
}

QString Question::getOp1()
{
    return question->getOp1();
}

QString Question::getOp2()
{
    return question->getOp2();
}

QString Question::getOp3()
{
    return question->getOp3();
}

QString Question::getOp4()
{
    return question->getOp4();
}

int Question::getAns()
{
    return question->getAns();
}

int Question::getSelectedOption()
{
    if(qnsOp1->isChecked())
    {
        return 1;
    }
    else if(qnsOp2->isChecked())
    {
        return 2;
    }
    else if(qnsOp3->isChecked())
    {
        return 3;
    }
    else if(qnsOp4->isChecked())
    {
        return 4;
    }
    else
    {
        return 0; // Student left question blank ):
    }
}

