#ifndef TESTSDB_H
#define TESTSDB_H

#include "Question.h"

class TestsDB
{
public:
    TestsDB();
    void addTest(QList<Question *> testQns);
    void deleteTest(int i);
    QList<Question *> getTest(int i);

    // call upon logging out
    void writeToFile();

    // for testing purposes only
    void forTesting(QWidget *parent);

    QList<QList<Question *> > getTests();
private:
    QList< QList<Question *> > tests;

};

#endif // TESTSDB_H
