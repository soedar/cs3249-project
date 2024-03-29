#include "Lesson.h"

Lesson::Lesson()
{
    this->setDate("");
    this->setTeacher(true);
    this->setLesson("");
    this->setMaxMarks(10);
    this->setTopic("");
    fileList = QStringList();
    imageList = QStringList();
    annotations = QList<CustomImage *>();
}

Lesson::Lesson(bool teacher, QString topic, QString lesson, QString date, int maxMarks)
{
        this->setTeacher(teacher);
        this->setTopic(topic);
        this->setLesson(lesson);
        this->setDate(date);
        this->setMaxMarks(maxMarks);
        fileList = QStringList();
        imageList = QStringList();
        annotations = QList<CustomImage *>();
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

void Lesson::setTeacher(bool teacher)
{
    this->teacher = teacher;
}

void Lesson::addFiles(QStringList *list)
{
    for (int i=0; i<list->size(); i++)
    {
        this->fileList.push_back(list->at(i));
    }
}

void Lesson::addImages(QStringList *list)
{
    for (int i=0; i<list->size(); i++)
    {
        this->imageList.push_back(list->at(i));
    }
}

void Lesson::addFiles(QStringList list)
{
    for (int i=0; i<list.size(); i++)
    {
        this->fileList.push_back(list.at(i));
    }
}

void Lesson::addImages(QStringList list)
{
    for (int i=0; i<list.size(); i++)
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
        for (int i=0; i<annotations.size(); i++)
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

void Lesson::setAnnos(QList<CustomImage *> tempList ,QList<int> numbers, QList<QPointF> positions, QStringList *annoText)
{
    this->annotations.clear();
    int count = 0;

    if (tempList.size() != numbers.size())
    {
        qDebug() << "Number of numbers != Number of Custom Images\nSomething went wrong\n";
    }

    for (int i=0; i<tempList.size(); i++)
    {
        CustomImage *image = tempList.at(i);

        for (int j=0; j<numbers.at(i); j++)
        {
            image->addAnno(new AnnotationGraphicsItem());
            image->setPos(j,positions.at(count), positions.at(count+1),annoText->at(j));
            count = count+2;
        }
        annotations.push_back(image);
    }
}

void Lesson::addCustomImage(int ind)
{
    CustomImage *tempImage = new CustomImage();
    tempImage->setIndex(ind);
    annotations.push_back(tempImage);
}

void Lesson::destroyCI(int ciIndex)
{
    CustomImage *image = annotations.takeAt(ciIndex);
    int numAnnos = image->getAnnos().size();
    for (int i=0; i<numAnnos; i++)
    {
        image->removeAnno(numAnnos-1-i);
    }
    delete image;

    for (int i=0; i<annotations.size(); i++)
    {
        annotations.at(i)->setIndex(i);
    }
}

void Lesson::addAnnos(int index, QList<AnnotationGraphicsItem *> tempList)
{
    CustomImage *image = new CustomImage();
    image->setAnnos(tempList);
    image->setIndex(index);
    this->annotations.push_back(image);
}

void Lesson::clear()
{
    fileList.clear();
    imageList.clear();
    int numCIs = annotations.size();

    for (int i=0; i<numCIs; i++)
    {
        CustomImage *tempImage = annotations.takeLast();
        tempImage->clear();
        delete tempImage;
    }
    annotations.clear();

}
