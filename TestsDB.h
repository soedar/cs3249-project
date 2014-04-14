#ifndef TESTSDB_H
#define TESTSDB_H

#include "Question.h"

class TestsDB
{
public:
    TestsDB();
    void addTest(QString lessonName, QList<Question *> testQns);
    QList<Question *> getTest(QString lessonName);
    void deleteTest(QString lessonName);
    void writeToFile();

    // for testing purposes only
    void forTesting(QWidget *parent);

private:
    QList< QPair<QString, QList<Question *> > > tests;

};

#endif // TESTSDB_H
