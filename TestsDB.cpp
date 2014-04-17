#include "TestsDB.h"

// Stores all the tests. A test consist of a list of questions.
TestsDB::TestsDB()
{
    // read from file to tests??


}

void TestsDB::addTest(QList<QuestionItem *> testQns)
{
    tests.append(testQns);
    qDebug("Successfully added test");
}

void TestsDB::saveTest(int index, QList<QuestionItem *> testQns)
{
    tests.removeAt(index);
    tests.insert(index,testQns);
}

void TestsDB::deleteTest(int i)
{
    tests.removeAt(i);
    qDebug("Successfully removed test");
}

QList<QuestionItem *> TestsDB::getTest(int i)
{
    return tests[i];
}

QList<QList<QuestionItem *> > TestsDB::getTests()
{
    return tests;
}

// for testing purposes only
/*
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
}*/

void TestsDB::clear()
{
    tests.clear();
}
