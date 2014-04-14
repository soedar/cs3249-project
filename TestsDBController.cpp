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

void TestsDBController::writeToFile() {
    tdb.writeToFile();
}

TestsDB TestsDBController::getDB() {
    return tdb;
}

void TestsDBController::addTest(QString testName,
                                QList<Question *> testQns) {

    tdb.addTest(testName, testQns);
}

QList<Question *> TestsDBController::getTest(QString testName) {
    return tdb.getTest(testName);
}

void TestsDBController::deleteTest(QString testName) {
    tdb.deleteTest(testName);
}



