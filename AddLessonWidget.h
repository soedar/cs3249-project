#ifndef ADDLESSONWINDOW_H
#define ADDLESSONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>

#include <LessonsDBController.h>
#include "ImageUploader.h"
#include "FileUploader.h"

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

    QTableWidget *fileTable;
    QTableWidget *imageTable;

    QPushButton *addTopic;
    QPushButton *dragFiles;
    QPushButton *dragImages;
    ImageUploader *uploader;
    FileUploader *uploaderF;

    bool editing;

private slots:
    void addStuff();
    void newTopic();

public slots:
    void prepare();

signals:
    void prepared();
    void saved();
    void added();




};

#endif // ADDLESSONWINDOW_H
