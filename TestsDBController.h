#ifndef TESTSDBCONTROLLER_H
#define TESTSDBCONTROLLER_H

#include "TestsDB.h"

class TestsDBController
{
public:
    TestsDBController();
    void init();

    static TestsDB* getDB();
    static QList<Question *> getTest(int i);

    // Only call at creation of lesson!
    static void addTest(QList<Question *> testQns);

    // only call at deletion lesson!
    static void deleteTest(int i);

private:
    static TestsDB tdb;
    bool initialized;

};

#endif // TESTSDBCONTROLLER_H
