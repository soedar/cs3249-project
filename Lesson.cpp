#include "Lesson.h"

Lesson::Lesson()
{
    this->setDate("");
    this->setTeacher(true);
    this->setLesson("");
    this->setMarks(0);
    this->setMaxMarks(0);
    this->setTopic("");
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

void Lesson::setDate(const QString &string)
{
    date = string;
}

void Lesson::setLesson(const QString &string)
{
    lesson = string;
}

void Lesson::setTopic(const QString &string)
{
    topic = string;
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