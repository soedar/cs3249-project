#include "TestsDBController.h"

TestsDB TestsDBController::tdb;

TestsDBController::TestsDBController()
{
    initialized = false;
}

void TestsDBController::init() {
    if(!initialized) {
        tdb = TestsDB();
        initialized = true;
    } else {
        return;
    }
}

TestsDB TestsDBController::getDB() {
    return tdb;
}

QList<Question *> TestsDBController::getTest(int i) {
    return tdb.getTest(i);
}

void TestsDBController::addTest(QList<Question *> testQns) {
    tdb.addTest(testQns);
}

void TestsDBController::deleteTest(int i) {
    tdb.deleteTest(i);
}

void TestsDBController::writeToFile() {
    tdb.writeToFile();
}



