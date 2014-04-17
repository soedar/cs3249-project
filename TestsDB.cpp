#include "TestsDB.h"

// Stores all the tests. A test consist of a list of questions.
TestsDB::TestsDB()
{
    // read from file to tests??


}

void TestsDB::addTest(QList<Question *> testQns)
{
    tests.append(testQns);
    qDebug("Successfully added test");
}

void TestsDB::saveTest(int index, QList<Question *> testQns)
{
    tests.removeAt(index);
    tests.insert(index,testQns);
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

QList< QList<Question *> > TestsDB::getTests() {
    return tests;
}

// for testing purposes only
void TestsDB::forTesting() {

    QList<Question *> tempTest = QList<Question *>();
    for(int i = 0; i < 5; i++) {
        Question *tempQns = new Question();
        tempQns->setQuestion(QString("This is question %1.").arg(i+1),
                             "op1", "op2", "op3", "op4", i);
        tempTest.append(tempQns);

        qDebug("%d qns have been added", i+1);
    }

    addTest(tempTest);
}
