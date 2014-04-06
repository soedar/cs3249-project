#ifndef ADDLESSONWINDOW_H
#define ADDLESSONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QUrl>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

#include <LessonsDB.h>
#include <Lesson.h>
#include <LessonsDBController.h>
#include "ImageUploader.h"


class AddLessonWindow : public QDialog
{
    Q_OBJECT
public:
    AddLessonWindow();
private:
    void createWidgets();

    QVBoxLayout *mainLayout;
    QLineEdit *lessonName;
    QComboBox *topicName;
    QLabel *uploadImages;
    QLabel *uploadFiles;
    QPushButton *uploadImageBtn;
    QPushButton *uploadFileBtn;
    QLabel *dragFiles;
    QLabel *dragImages;
    ImageUploader *uploader;


signals:

public slots:

};

#endif // ADDLESSONWINDOW_H
