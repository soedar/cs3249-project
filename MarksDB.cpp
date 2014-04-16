#include "MarksDB.h"

static QMap<QString, QMap<int,int>> markMap;

MarksDB::MarksDB()
{
}

int MarksDB::getMark(QString email, int lessonId)
{
    if (!markMap.contains(email))
    {
        return -1;
    }
    QMap<int, int> map = markMap.value(email);
    return map.value(lessonId);
}

void MarksDB::addMark(QString email,int lessonId, int mark)
{
    if (!markMap.contains(email))
    {
        markMap.insert(email,QMap<int,int>());
    }
    QMap<int, int> map = markMap.take(email);
    if (!map.contains(lessonId))
    {
        map.insert(lessonId,mark);
    }
    else
    {

    }
    markMap.insert(email,map);
}


void MarksDB::setMark(QString email,int lessonId, int mark)
{
    if (!markMap.contains(email))
    {
        return;
    }
    QMap<int, int> map = markMap.take(email);
    if (!map.contains(lessonId))
    {

    }
    else
    {
        map.take(lessonId);
        map.insert(lessonId,mark);
    }
    markMap.insert(email,map);

}

QMap<int,int> MarksDB::getMarks(QString email)
{
    if (markMap.contains(email))
    {
        return markMap.value(email);
    }
    else
    {
        return QMap<int,int>();
    }
}

QMap<QString, QMap<int, int> > MarksDB::getData()
{
    return markMap;
}

void MarksDB::deleteLesson(int lessonId)
{
    QList<QString> listStudents = markMap.uniqueKeys();

    for (int i=0; i<listStudents.size(); i++)
    {
        QString name = listStudents.at(i);

        QMap<int,int> tempMap = markMap.take(name);

        if (tempMap.contains(lessonId))
        {
            tempMap.remove(lessonId);
        }
        if (tempMap.size() > 0)
        {
            markMap.insert(name,tempMap);
        }
    }
}

void MarksDB::clear()
{
    markMap.clear();
}
