#ifndef LESSONSDBCONTROLLER_H
#define LESSONSDBCONTROLLER_H

#include "LessonsDB.h"

class LessonsDBController
{
public:
    static void init();
    static LessonsDB* getDB();
    static void addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images);
    static void editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList);
    static void deleteItemAt(int index);
    static void setIndex(int ind);
    static int getIndex(); 
    static void addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions, QStringList *annoText);
    static void addTopic(const QString &topicName);
    static void destroyCI(int lIndex, int ciIndex);
    static void editFilesImages(int index, const QString &lessonName, const QString &topicName, QStringList *files, int fBypass, QStringList *images, int iBypass);
    static void clear();

    void editMaxMark(int index, int newMark);
};

#endif // LESSONDBCONTROLLER_H
