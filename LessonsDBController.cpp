#include "LessonsDBController.h"

LessonsDB LessonsDBController::ldb;
int LessonsDBController::editIndex;

LessonsDBController::LessonsDBController()
{
    initialized = false;
}
void LessonsDBController::init()
{
    if (!initialized)
    {
        ldb = LessonsDB();
        initialized = true;
    }
    else
    {
        return;
    }
}

LessonsDB LessonsDBController::getDB()
{
    return ldb;
}

void LessonsDBController::deleteItemAt(int index)
{
    ldb.deleteItemAt(index);
}

void LessonsDBController::addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions)
{
    ldb.addLesson(isTeacher, lessonName, topicName, date, marks, maxMarks, files, images, list, numbers, positions);
}

void LessonsDBController::addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images)
{
    ldb.addLesson(lessonName, topicName, files, images);
}

void LessonsDBController::editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList)
{
    ldb.editLesson(index,lessonName,topicName,annoList);
}

void LessonsDBController::readFile(const QString &string)
{
    return;
}
void LessonsDBController::saveFile(const QString &string)
{
    return;
}

int LessonsDBController::getIndex()
{
    return editIndex;
}

void LessonsDBController::setIndex(int ind)
{
    editIndex = ind;
}
