#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui>

class Question : public QWidget
{
    Q_OBJECT
public:
    Question(QWidget *parent);
    QGroupBox *createQuestion(const QString &string, const QString &string,
                              const QString &string, const QString &string,
                              const QString &string);
    bool isCorrect();
    int getSelectedOption();
    int getAns();
    void setAns(int ans);

private:
    QVBoxLayout *vbox;
    QGroupBox *questionName;
    QRadioButton *op1;
    QRadioButton *op2;
    QRadioButton *op3;
    QRadioButton *op4;
    int answer;

};

#endif // QUESTION_H
