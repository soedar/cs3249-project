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


#include <LessonsDBController.h>
#include "ImageUploader.h"
#include "FileUploader.h"

class AddLessonWindow : public QDialog
{
    Q_OBJECT
public:
    AddLessonWindow();
    QPushButton* getBtn();
private:
    void createWidgets();
    void addStuff();

    QVBoxLayout *mainLayout;
    QLineEdit *lessonName;
    QComboBox *topicName;
    QLabel *uploadImages;
    QLabel *uploadFiles;
    QPushButton *uploadBtn;
    QPushButton *dragFiles;
    QPushButton *dragImages;
    ImageUploader *uploader;
    FileUploader *uploaderF;


signals:

public slots:

};

#endif // ADDLESSONWINDOW_H
