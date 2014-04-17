#ifndef TESTSDBCONTROLLER_H
#define TESTSDBCONTROLLER_H

#include "TestsDB.h"

class TestsDBController
{
public:
    TestsDBController();
    void init();

    static TestsDB* getDB();
    static QList<QuestionItem *> getTest(int i);

    // Only call at creation of lesson!
    static void addTest(QList<QuestionItem *> testQns);

    // only call at deletion lesson!
    static void deleteTest(int i);

    static void saveTest(int index, QList<QuestionItem *> testQns);
    static void clear();
private:
    static TestsDB tdb;
    bool initialized;

};

#endif // TESTSDBCONTROLLER_H
