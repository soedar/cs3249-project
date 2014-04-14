#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui>

class Question : public QWidget
{
    Q_OBJECT
public:
    Question(QWidget *parent);
    QGroupBox *createQuestion(QString name, QString op1,
                             QString op2, QString op3,
                             QString op4);
    bool isCorrect();
    int getSelectedOption();
    int getAns();
    void setAns(int ans);

private:
    QVBoxLayout *vbox;
    QGroupBox *qnsName;
    QRadioButton *qnsOp1;
    QRadioButton *qnsOp2;
    QRadioButton *qnsOp3;
    QRadioButton *qnsOp4;
    int answer;

};

#endif // QUESTION_H
