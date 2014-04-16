#ifndef STUDENT_LESSONWIDGET_H
#define STUDENT_LESSONWIDGET_H

#include <QDialog>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include "Lesson.h"
#include "MenuWidget.h"
#include <QLabel>
#include <CustomScene.h>

class StudentLessonWidget : public QDialog
{
    Q_OBJECT
public:
    StudentLessonWidget();
    //QWidget *pdfWidget;
    //QWidget *imageWidget;
    MenuWidget *menuWidget;
<<<<<<< HEAD
    void prepare(Lesson *less);
=======
    QTextEdit *textEditWidget;
>>>>>>> 347624bff9bef64796a330839e19741b16119093

private:
    Lesson *lesson;
    QLabel *lessonName;
    QLabel *topicName;
    QGraphicsView *imageView;
    CustomScene *scene;
    QGraphicsPixmapItem *image;
    //QTextEdit *pdfView;
    QMenu *transitMenu;

    QStringList *imageUrls;
    QList<CustomImage *> annotations;
    int currentIndex;

    double zoom;
    double maxZoom;
    double minZoom;

    void createWidgets();
    void initImages();
    void setImage(int index);

    void resizeEvent(QResizeEvent *event);

protected:
    void wheelEvent(QWheelEvent *event);

signals:
    void prepared();
    void transitLessons();
    void logOut();

public slots:

    void previousImage();
    void nextImage();
    void clearScene();
    void refreshScene();
    void transit();
    void exit();
};

#endif
