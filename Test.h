#ifndef TEST_H
#define TEST_H

#include <QtGui>
#include <Question.h>

class Test
{
public:
    Test();

    void addQuestion(const QString &string, const QString &string,
                     const QString &string, const QString &string,
                     const QString &string, int ans);
    void deleteTest();

private:
    void setLayout();

    QList<Question *> questionList;
};

#endif // TEST_H
