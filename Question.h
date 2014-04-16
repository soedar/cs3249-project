#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui>

class Question : public QWidget
{
    Q_OBJECT
public:
    Question(QWidget *parent = 0);
    QGroupBox *setQuestion(QString name, QString op1,
                           QString op2, QString op3,
                           QString op4, int ans);
    bool isCorrect();
    int getSelectedOption();
    int getAns();

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
