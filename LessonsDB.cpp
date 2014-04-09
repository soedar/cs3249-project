#include "LessonsDB.h"
#include "qdebug.h"

LessonsDB::LessonsDB()
{
    //Initial Lesson items
    Lesson tempLesson;

    tempLesson.setDate("1/1/2014");
    tempLesson.setLesson("1: The Skull");
    tempLesson.setMarks(0);
    tempLesson.setMaxMarks(10);
    tempLesson.setTeacher(true);
    tempLesson.setTopic("The Human Skeleton");
    lessons.push_back(tempLesson);

    tempLesson.setDate("2/1/2014");
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

void LessonsDB::deleteItemAt(int index)
{
    lessons.removeAt(index);
}

void LessonsDB::addItemAtIndex(int index, Lesson l)
{
    lessons.insert(index,l);
}

void LessonsDB::addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images)
{
    Lesson tempLesson;

    QDate today = QDate::currentDate();
    QString todayStr = today.toString("d/M/yyyy");

    tempLesson.setDate(todayStr);
    tempLesson.setLesson(lessonName);
    tempLesson.setMarks(0);
    tempLesson.setMaxMarks(10);
    tempLesson.setTeacher(true);
    tempLesson.setTopic(topicName);
    tempLesson.addFiles(files);
    tempLesson.addImages(images);
    qDebug("Adding new item in LessonsDB\n");
    lessons.push_back(tempLesson);
}

void LessonsDB::editLesson(int index, const QString &lessonName, const QString &topicName, QList<AnnotationGraphicsItem *> annoList)
{
    Lesson tempLesson;

    QDate today = QDate::currentDate();
    QString todayStr = today.toString("d/M/yyyy");

    Lesson newLesson = Lesson();
    newLesson.setDate(todayStr);
    newLesson.setLesson(lessonName);
    newLesson.setTeacher(tempLesson.isTeacher());
    newLesson.setMarks(tempLesson.getMarks());
    newLesson.setMaxMarks(tempLesson.getMaxMarks());
    newLesson.setTopic(topicName);
    newLesson.setAnnos(annoList);
    newLesson.addFiles(tempLesson.getFileList());
    newLesson.addImages(tempLesson.getImageList());

    deleteItemAt(index);
    addItemAtIndex(index,newLesson);
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
