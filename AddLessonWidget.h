#ifndef ADDLESSONWINDOW_H
#define ADDLESSONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

#include <LessonsDBController.h>
#include "ImageUploader.h"
#include "FileUploader.h"

class Overseer;

class AddLessonWidget : public QWidget
{
    Q_OBJECT
public:
    AddLessonWidget();
    QPushButton *uploadBtn;

private:
    void createWidgets();

    QVBoxLayout *mainLayout;
    QLineEdit *lessonName;
    QLineEdit *addNewTopic;
    QComboBox *topicName;
    QLabel *uploadImages;
    QLabel *uploadFiles;

    QPushButton *addTopic;
    QPushButton *dragFiles;
    QPushButton *dragImages;
    ImageUploader *uploader;
    FileUploader *uploaderF;

private slots:
    void addStuff();
    void newTopic();


};

#endif // ADDLESSONWINDOW_H
