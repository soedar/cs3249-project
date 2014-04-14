#include "Lesson.h"

Lesson::Lesson()
{
    this->setDate("");
    this->setTeacher(true);
    this->setLesson("");
    this->setMarks(0);
    this->setMaxMarks(0);
    this->setTopic("");
    fileList = QStringList();
    imageList = QStringList();
    annotations = QList<CustomImage *>();
}

Lesson::Lesson(bool teacher, QString topic, QString lesson, QString date, int maxMarks, int marks)
{
        this->setTeacher(teacher);
        this->setTopic(topic);
        this->setLesson(lesson);
        this->setDate(date);
        this->setMaxMarks(maxMarks);
        this->setMarks(marks);
}

//Getters and Setters

QString Lesson::getDate()
{
    return date;
}

QString Lesson::getLesson()
{
    return lesson;
}

int Lesson::getMarks()
{
    return marks;
}

int Lesson::getMaxMarks()
{
    return maxMarks;
}

QString Lesson::getTopic()
{
    return topic;
}

bool Lesson::isTeacher()
{
    return teacher;
}

QStringList Lesson::getImageList()
{
    return imageList;
}

QStringList Lesson::getFileList()
{
    return fileList;
}

void Lesson::setDate(const QString &string)
{
    this->date = string;
}

void Lesson::setLesson(const QString &string)
{
    this->lesson = string;
}

void Lesson::setTopic(const QString &string)
{
    this->topic = string;
}

void Lesson::setMaxMarks(int marks)
{
    this->maxMarks = marks;
}

void Lesson::setMarks(int marks)
{
    this->marks = marks;
}

void Lesson::setTeacher(bool teacher)
{
    this->teacher = teacher;
}

void Lesson::addFiles(QStringList *list)
{
    for (int i=0; i<list->count(); i++)
    {
        this->fileList.push_back(list->at(i));
    }
}

void Lesson::addImages(QStringList *list)
{
    for (int i=0; i<list->count(); i++)
    {
        this->imageList.push_back(list->at(i));
    }
}

void Lesson::addFiles(QStringList list)
{
    for (int i=0; i<list.count(); i++)
    {
        this->fileList.push_back(list.at(i));
    }
}

void Lesson::addImages(QStringList list)
{
    for (int i=0; i<list.count(); i++)
    {
        this->imageList.push_back(list.at(i));
    }
}
void Lesson::removeFile(const QString &string)
{
    this->fileList.removeOne(string);
}

QList<CustomImage *> Lesson::getAnnos()
{
    return this->annotations;
}


void Lesson::removeImage(const QString &string)
{
    int index = imageList.indexOf(string);
    if (index > -1)
    {
        for (int i=0; i<annotations.size();i++)
        {
            CustomImage *image = annotations.at(i);
            if (image->getIndex() == index)
            {
                annotations.removeAt(i);
                break;
            }
        }
        for (int i=0; i<annotations.size(); i++)
        {
            CustomImage *image = annotations.at(i);
            if (image->getIndex() > index)
            {
                annotations.at(i)->setIndex(image->getIndex()-1);
                break;
            }
        }
    }
    this->imageList.removeOne(string);
}

void Lesson::setAnnos(QList<CustomImage *> tempList)
{
    this->annotations.clear();

    for (int i=0; i<tempList.size(); i++)
    {
        this->annotations.push_back(tempList.at(i));
    }
}

void Lesson::addCustomImage(int ind)
{
    CustomImage *tempImage = new CustomImage();
    tempImage->setIndex(ind);
    annotations.push_back(tempImage);
}

void Lesson::addAnnos(int index, QList<AnnotationGraphicsItem *> tempList)
{
    CustomImage *image = new CustomImage();
    image->setAnnos(tempList);
    image->setIndex(index);
    this->annotations.push_back(image);
}
