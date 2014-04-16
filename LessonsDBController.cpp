#include "TestWidget.h"

static LessonsDB *ldb;
static int editIndex;
static bool initialized;

void LessonsDBController::init()
{
    if (!initialized)
    {
        ldb = new LessonsDB();
        initialized = true;
    }
    else
    {
        return;
    }
}

LessonsDB* LessonsDBController::getDB()
{
    return ldb;
}

void LessonsDBController::deleteItemAt(int index)
{
    ldb->deleteItemAt(index);
    TestsDBController::deleteTest(index);
}

void LessonsDBController::addLesson(bool isTeacher, const QString &lessonName, const QString &topicName, const QString &date, int marks, int maxMarks, QStringList *files, QStringList *images, QList<CustomImage *> list, QList<int> numbers, QList<QPointF> positions)
{
    ldb->addLesson(isTeacher, lessonName, topicName, date, marks, maxMarks, files, images, list, numbers, positions);
    //TestsDBController::addTest(QList<Question *>());
}

void LessonsDBController::addTopic(const QString &topicName)
{
    ldb->addTopic(topicName);
}

void LessonsDBController::destroyCI(int lIndex, int ciIndex)
{
    ldb->destroyCI(lIndex,ciIndex);
}

void LessonsDBController::editFilesImages(int index, const QString &lessonName, const QString &topicName, QStringList *files, int fBypass, QStringList *images, int iBypass)
{
    ldb->editFilesImages(index,lessonName,topicName,files,fBypass,images,iBypass);
}

void LessonsDBController::addLesson(const QString &lessonName, const QString &topicName, QStringList *files, QStringList *images)
{
    ldb->addLesson(lessonName, topicName, files, images);
    TestsDBController::addTest(QList<Question *>());
}

void LessonsDBController::editLesson(int index, const QString &lessonName, const QString &topicName, QList<CustomImage *> annoList)
{
    ldb->editLesson(index,lessonName,topicName,annoList);
}

int LessonsDBController::getIndex()
{
    return editIndex;
}

void LessonsDBController::setIndex(int ind)
{
    editIndex = ind;
}
void LessonsDBController::clear()
{
    ldb->clear();
}
