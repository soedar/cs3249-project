#ifndef TESTSDB_H
#define TESTSDB_H

#include <Question.h>

class TestsDB
{
public:
    TestsDB();
    QList<Question *> getTests();
};

#endif // TESTSDB_H
