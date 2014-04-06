#ifndef LESSONSDB_H
#define LESSONSDB_H
#include <QStringList>
#include <QList>
#include "Lesson.h"

class LessonsDB
{

public:
    LessonsDB();
    QList<Lesson> getLessons();
    QStringList getTopics();
    void addTopic(const QString &string);
    void addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images);

private:
    QList<Lesson> lessons;
    QStringList topics;
};

#endif // LESSONSDB_H
