#ifndef LESSONSDB_H
#define LESSONSDB_H

#include <QList>
#include "Lesson.h"
#include <QDate>

class LessonsDB
{

public:
    LessonsDB();
    QList<Lesson> getLessons();
    QStringList getTopics();
    void addTopic(const QString &string);
    void addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images);
    void editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList);
    void deleteItemAt(int index);
    void addItemAtIndex(int index, Lesson l);

private:
    QList<Lesson> lessons;
    QStringList topics;
};

#endif // LESSONSDB_H
