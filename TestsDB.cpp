#include "TestsDB.h"

// Stores all the tests. A test consist of a list of questions.
TestsDB::TestsDB()
{
    // read from file to tests??


}

void TestsDB::addTest(QList<Question *> testQns) {
    tests.append(testQns);
    qDebug("Successfully added test");
}

void TestsDB::deleteTest(int i) {
    tests.removeAt(i);
    qDebug("Successfully removed test");
}

QList<Question *> TestsDB::getTest(int i) {
    return tests[i];

/*    // return empty QList if there is no test with that index
    qDebug("Test");
    return QList<Question *>();
    */
}

void TestsDB::saveTest(int i, QList<Question *> updatedQns) {
    tests.replace(i, updatedQns);
}

void TestsDB::writeToFile() {
    // write tests to file??
}

// for testing purposes only
void TestsDB::forTesting(QWidget *parent) {

    QList<Question *> tempTest = QList<Question *>();
    for(int i = 0; i < 5; i++) {
        Question *tempQns = new Question(parent);
        tempQns->setQuestion("This is question " + i, "op1",
                             "op2", "op3", "op4", 2);
        tempTest.append(tempQns);
    }

    addTest(tempTest);
}
