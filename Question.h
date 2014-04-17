#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui>
#include <QuestionItem.h>
#include <QGridLayout>

class Question : public QWidget
{
    Q_OBJECT
public:
    Question();
    void setQuestion(QString name, QString op1,
                           QString op2, QString op3,
                           QString op4, int ans);

    void setQuestion(QuestionItem *item);
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

    QuestionItem* getQuestion();

    void saveQuestion();

    QGroupBox *qnsName;
    QGroupBox *qnsEdit;

    QRadioButton *qnsOp1;
    QRadioButton *qnsOp2;
    QRadioButton *qnsOp3;
    QRadioButton *qnsOp4;

    QLineEdit *editName;
    QLineEdit *editOp1;
    QLineEdit *editOp2;
    QLineEdit *editOp3;
    QLineEdit *editOp4;
    QComboBox *editAns;

    void setLayoutStudent();
    void setLayoutTeacher();
private:
    QVBoxLayout *mainLayoutStudent;
    QVBoxLayout *mainLayoutTeacher;

    QGridLayout *gridTeacher;
    QVBoxLayout *vboxStudent;

    QuestionItem *question;

};

#endif // QUESTION_H
