#include "LessonsDB.h"

LessonsDB::LessonsDB()
{
    //lessons = new QList<Lesson>();

    Lesson tempLesson;

    tempLesson.setDate("1/1/4");
    tempLesson.setLesson("1: The Skull");
    tempLesson.setMarks(0);
    tempLesson.setMaxMarks(10);
    tempLesson.setTeacher(true);
    tempLesson.setTopic("The Human Skeleton");
    lessons.push_back(tempLesson);

    tempLesson.setDate("2/1/4");
    tempLesson.setLesson("2: The Hand");
    lessons.push_back(tempLesson);
    addTopic("The Human Skeleton");
}

QList<Lesson> LessonsDB::getLessons()
{
    return lessons;
}

QStringList LessonsDB::getTopics()
{
    return topics;
}

void LessonsDB::addTopic(const QString &string)
{

    if(topics.contains(string))
    {
        return;
    }
    else
    {
        topics.push_back(string);
    }
}
