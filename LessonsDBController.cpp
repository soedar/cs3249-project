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

void LessonsDBController::readFile(const QString &string)
{
    return;
}
void LessonsDBController::saveFile(const QString &string)
{
    return;
}
