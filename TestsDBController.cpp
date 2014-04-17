#include "TestsDBController.h"

TestsDB TestsDBController::tdb;

TestsDBController::TestsDBController()
{
}

TestsDB* TestsDBController::getDB() {
    return &tdb;
}

QList<Question *> TestsDBController::getTest(int i) {
    return tdb.getTest(i);
}

void TestsDBController::addTest(QList<Question *> testQns) {
    tdb.addTest(testQns);
}

void TestsDBController::saveTest(int index, QList<Question *> testQns)
{
    tdb.saveTest(index, testQns);
}

void TestsDBController::deleteTest(int i) {
    tdb.deleteTest(i);
}


