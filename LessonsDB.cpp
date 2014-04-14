#include "LessonsDB.h"
#include "qdebug.h"

LessonsDB::LessonsDB()
{
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

void LessonsDB::addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions)
{
    Lesson tempLesson = Lesson();

    tempLesson.setTeacher(isTeacher);
    tempLesson.setLesson(lessonName);
    tempLesson.setTopic(topicName);
    tempLesson.setDate(date);
    tempLesson.setMarks(marks);
    tempLesson.setMaxMarks(maxMarks);
    tempLesson.addFiles(files);
    tempLesson.addImages(images);
    tempLesson.setAnnos(list,numbers,positions);
    lessons.push_back(tempLesson);
    qDebug() << "New Lesson Added, No.of lessons = " << lessons.size() << "\n";
    addTopic("The Human Skeleton");

}

void LessonsDB::addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images)
{
    Lesson tempLesson = Lesson();

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
    for (int i=0; i<images->size(); i++)
    {
        tempLesson.addCustomImage(i);
    }
    qDebug("Adding new item in LessonsDB\n");
    addTopic("The Human Skeleton");
    lessons.push_back(tempLesson);

    qDebug() << "Lesson, File size : " << tempLesson.getFileList().size() << "  Image size" << tempLesson.getImageList().size() << "\n";
}

void LessonsDB::editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList)
{
    Lesson tempLesson = lessons.at(index);

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
