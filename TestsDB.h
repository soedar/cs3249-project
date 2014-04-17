#ifndef TESTSDB_H
#define TESTSDB_H

#include "Question.h"
#include "QuestionItem.h"

class TestsDB
{
public:
    TestsDB();
    void addTest(QList<QuestionItem *> testQns);
    void deleteTest(int i);
    QList<QuestionItem *> getTest(int i);

    // for testing purposes only
    //void forTesting();

    QList<QList<QuestionItem *> > getTests();
    void saveTest(int index, QList<QuestionItem *> testQns);
    void clear();
private:
    QList< QList<QuestionItem *> > tests;

};

#endif // TESTSDB_H
