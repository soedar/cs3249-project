#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui>

class Question : public QWidget
{
    Q_OBJECT
public:
    Question();
    QGroupBox *setQuestion(QString name, QString op1,
                           QString op2, QString op3,
                           QString op4, int ans);
    bool isCorrect();
    int getSelectedOption();

    void setQnsName(QString qns);
    void setOp1(QString op1);
    void setOp2(QString op2);
    void setOp3(QString op3);
    void setOp4(QString op4);
    void setAns(int ans);

    QString getQnsName();
    QString getOp1();
    QString getOp2();
    QString getOp3();
    QString getOp4();
    int getAns();

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *vbox;
    QGroupBox *qnsName;
    QRadioButton *qnsOp1;
    QRadioButton *qnsOp2;
    QRadioButton *qnsOp3;
    QRadioButton *qnsOp4;

    QString questionName;
    QString option1;
    QString option2;
    QString option3;
    QString option4;
    int answer;

};

#endif // QUESTION_H
