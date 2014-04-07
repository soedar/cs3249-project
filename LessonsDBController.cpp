#include "LessonsDBController.h"

LessonsDB LessonsDBController::ldb;

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

void LessonsDBController::addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images)
{
    ldb.addLesson(lessonName, topicName, files, images);
}

void LessonsDBController::readFile(const QString &string)
{
    return;
}
void LessonsDBController::saveFile(const QString &string)
{
    return;
}
