#ifndef QUESTIONITEM_H
#define QUESTIONITEM_H


#include <QString>

class QuestionItem
{
public:
    QuestionItem();

    void setQnName(QString string);
    void setOp1(QString string);
    void setOp2(QString string);
    void setOp3(QString string);
    void setOp4(QString string);
    void setAns(int ans);

    QString getQnName();
    QString getOp1();
    QString getOp2();
    QString getOp3();
    QString getOp4();
    int getAns();

private:
    QString questionName;
    QString option1;
    QString option2;
    QString option3;
    QString option4;
    int answer;

};

#endif // QUESTIONITEM_H
