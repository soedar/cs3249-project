#ifndef LESSONSDBCONTROLLER_H
#define LESSONSDBCONTROLLER_H

#include "LessonsDB.h"

class LessonsDBController
{

public:
    LessonsDBController();
    void init();
    void readFile(const QString &string);
    void saveFile(const QString &string);
    static LessonsDB getDB();
private:
    static LessonsDB ldb;
    bool initialized;
};

#endif // LESSONDBCONTROLLER_H
