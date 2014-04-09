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
    static void addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images);
    static void editLesson(int index, const QString &lessonName, const QString &topicName, QList<AnnotationGraphicsItem *> annoList);
    static void deleteItemAt(int index);
    static void setIndex(int ind);
    static int getIndex();

private:
    static LessonsDB ldb;
    bool initialized;
    static int editIndex;
};

#endif // LESSONDBCONTROLLER_H
