#ifndef LESSON_H
#define LESSON_H

#include <QString>

class Lesson
{

public:
    Lesson();
    Lesson(bool teacher, QString topic, QString lesson, QString date, int maxMarks, int marks);

    QString getTopic();
    QString getLesson();
    QString getDate();
    int getMaxMarks();
    int getMarks();
    bool isTeacher();

    void setTopic(const QString &string);
    void setLesson(const QString &string);
    void setDate(const QString &string);
    void setMaxMarks(int marks);
    void setMarks(int marks);
    void setTeacher(bool teacher);

private:
    bool teacher;
    QString topic;
    QString lesson;
    QString date;
    int maxMarks;
    int marks;

};

#endif // LESSON_H
