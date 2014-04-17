#include "TestsDBController.h"

TestsDB TestsDBController::tdb;

TestsDBController::TestsDBController()
{
}

TestsDB* TestsDBController::getDB()
{
    return &tdb;
}

QList<QuestionItem *> TestsDBController::getTest(int i)
{
    return tdb.getTest(i);
}

void TestsDBController::addTest(QList<QuestionItem *> testQns)
{
    tdb.addTest(testQns);
}

void TestsDBController::saveTest(int index, QList<QuestionItem *> testQns)
{
    tdb.saveTest(index, testQns);
}

void TestsDBController::deleteTest(int i)
{
    tdb.deleteTest(i);
}

void TestsDBController::clear()
{
    tdb.clear();
}


