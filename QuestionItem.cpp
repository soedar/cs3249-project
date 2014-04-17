#include "QuestionItem.h"

QuestionItem::QuestionItem()
{

}

void QuestionItem::setQnName(QString qns)
{
    questionName = qns;
}

void QuestionItem::setOp1(QString op1)
{
    option1 = op1;
}

void QuestionItem::setOp2(QString op2)
{
    option2 = op2;
}

void QuestionItem::setOp3(QString op3)
{
    option3 = op3;
}

void QuestionItem::setOp4(QString op4)
{
    option4 = op4;
}

void QuestionItem::setAns(int ans)
{
    answer = ans;
}

QString QuestionItem::getQnName()
{
    return questionName;
}

QString QuestionItem::getOp1()
{
    return option1;
}

QString QuestionItem::getOp2()
{
    return option2;
}

QString QuestionItem::getOp3()
{
    return option3;
}

QString QuestionItem::getOp4()
{
    return option4;
}

int QuestionItem::getAns()
{
    return answer;
}
