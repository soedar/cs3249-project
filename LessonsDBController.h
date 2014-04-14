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
    static void editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList);
    static void deleteItemAt(int index);
    static void setIndex(int ind);
    static int getIndex(); 
    static void addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions);
    //static void addLesson(bool isTeacher, QString lessonName, QString topicName, QString date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions);
private:
    static LessonsDB ldb;
    bool initialized;
    static int editIndex;

    QString dataPath;
};

#endif // LESSONDBCONTROLLER_H
