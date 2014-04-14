#ifndef LESSON_H
#define LESSON_H

#include <QString>
#include <QStringList>
#include <CustomImage.h>

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
    QList<CustomImage *> getAnnos();
    void addAnnos(int index, QList<AnnotationGraphicsItem *> tempList);
    void setAnnos(QList<CustomImage *> tempList);
    void addCustomImage(int ind);

private:
    bool teacher;
    QString topic;
    QString lesson;
    QString date;
    int maxMarks;
    int marks;
    QStringList imageList;
    QStringList fileList;
    QList<CustomImage *> annotations;

};

#endif // LESSON_H
