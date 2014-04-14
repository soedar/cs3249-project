#ifndef TESTSDBCONTROLLER_H
#define TESTSDBCONTROLLER_H

#include "TestsDB.h"

class TestsDBController
{
public:
    TestsDBController();
    void init();
    void writeToFile();

    static TestsDB getDB();
    static void addTest(QString testName, QList<Question *> testQns);
    static QList<Question *> getTest(QString testName);
    static void deleteTest(QString testName);

private:
    static TestsDB tdb;
    bool initialized;

};

#endif // TESTSDBCONTROLLER_H
