#ifndef TESTSDBCONTROLLER_H
#define TESTSDBCONTROLLER_H

#include "TestsDB.h"

class TestsDBController
{
public:
    TestsDBController();
    void init();

    static TestsDB getDB();
    static QList<Question *> getTest(int i);

    // Call when saving an edited test.
    static void saveTest(int i, QList<Question *> updatedQns);

    // Only call at creation of lesson!
    static void addTest(QList<Question *> testQns);

    // only call at deletion lesson!
    static void deleteTest(int i);

    // Call when logging out
    static void writeToFile();

private:
    static TestsDB tdb;
    bool initialized;

};

#endif // TESTSDBCONTROLLER_H
