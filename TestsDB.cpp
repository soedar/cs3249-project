#include "TestsDB.h"

// Stores all the tests. A test consist of
// its name and a list of questions.
TestsDB::TestsDB()
{
    // read from file to tests??


}

// for testing purposes only
void TestsDB::forTesting(QWidget *parent) {

    for(int i = 0; i < 5; i++) {
        Question *tempQns = new Question(parent);
        tempQns->setQuestion("This is question " + i, "op1",
                             "op2", "op3", "op4", 2);
    }
}

void TestsDB::addTest(QString lessonName, QList<Question *> testQns) {
    tests.append(qMakePair(lessonName, testQns));
    qDebug("Successfully added test");
}

QList<Question *> TestsDB::getTest(QString lessonName) {
    for(int i = 0; i < tests.length(); i++) {
        if(tests[i].first.compare(lessonName) == 0) {
            return tests[i].second;
        }
    }

    // return empty QPair if there is no test with that name
    qDebug("Cannot find test!");
    return QList<Question *>();
}

void TestsDB::deleteTest(QString lessonName) {
    for(int i = 0; i < tests.length(); i++) {
        if(tests[i].first.compare(lessonName) == 0) {
            tests.removeAt(i);
            qDebug("Successfully removed test");
        }
    }

}


// to be called upon exiting app?
void TestsDB::writeToFile() {
    // write tests to file??
}
