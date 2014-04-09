#ifndef LESSON_H
#define LESSON_H

#include <QString>
#include <QStringList>
#include <AnnotationGraphicsItem.h>

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
    QStringList getFileList();
    QStringList getImageList();
    void addImages(QStringList *list);
    void addFiles(QStringList *list);
    void addImages(QStringList list);
    void addFiles(QStringList list);
    void removeImage(const QString &string);
    void removeFile(const QString &string);
    QList<AnnotationGraphicsItem *> getAnnos();
    void addAnnos(QList<AnnotationGraphicsItem *> tempList);
    void setAnnos(QList<AnnotationGraphicsItem *> tempList);

private:
    bool teacher;
    QString topic;
    QString lesson;
    QString date;
    int maxMarks;
    int marks;
    QStringList imageList;
    QStringList fileList;
    QList<AnnotationGraphicsItem *> annotations;

};

#endif // LESSON_H
