#ifndef MARKSDB_H
#define MARKSDB_H

#include <QList>
#include <QMap>
#include <QString>


class MarksDB
{
public:
    MarksDB();

    static int getMark(QString email, int lessonId);
    static void addMark(QString email, int lessonId, int mark);
    static void setMark(QString email, int lessonId, int mark);
    static QMap<int, int> getMarks(QString email);
    static QMap<QString, QMap<int,int>> getData();
    static void deleteLesson(int lessonId);
    static void clear();
};

#endif // MARKSDB_H
