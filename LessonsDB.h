#ifndef LESSONSDB_H
#define LESSONSDB_H

#include <QList>
#include "Lesson.h"
#include <QDate>
#include <QObject>

class LessonsDB : public QObject
{
    Q_OBJECT
public:
    LessonsDB();
    QList<Lesson> getLessons();
    QStringList getTopics();
    void addTopic(const QString &string);
    void addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images);
    void editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList);
    void deleteItemAt(int index);
    void addItemAtIndex(int index, Lesson l);
    void addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions, QStringList *annoText);
    void destroyCI(int lIndex, int ciIndex);
    void editFilesImages(int index, const QString &lessonName, const QString &topicName, QStringList *files, int fBypass, QStringList *images, int iBypass);
    void clear();

private:
    QList<Lesson> lessons;
    QStringList topics;

signals:
    void newLessonCreated();
};

#endif // LESSONSDB_H
