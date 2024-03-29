#ifndef LESSONWIDGET_H
#define LESSONWIDGET_H

#include <QDialog>
#include <QGraphicsView>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <LessonsDBController.h>
#include <QPixmap>
#include <QWheelEvent>
#include <QToolBar>
#include <QAction>
#include <CustomImage.h>
#include <CustomScene.h>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGraphicsPixmapItem>
#include "TestWidget.h"


class LessonWidget : public QDialog
{
    Q_OBJECT
public:
    LessonWidget();


private:
    QGraphicsView *imageView;
    CustomScene *scene;
    QGraphicsPixmapItem *image;
    QTextEdit *pdfView;
    QMenu *transitMenu;
    QToolBar *toolbar;

    QAction *selectAction; //Disables Movement, Enables Multi-Selection
    QAction *handAction; // Enables Movement, Disables Multi-Selection
    QAction *annotationAction; //Adds a new annotation to a predefined spot in the scene
    QAction *deleteAction; //Click once to change icon, click again to select an item, click again to delete selected items
    QAction *imageAction; //Manages files and images
    QAction *saveAction; //Saves and exits, working for now
    QAction *testAction; //Transits to the test widget
    QAction *rightAction;
    QAction *leftAction;

    QLineEdit *lessonName;
    QComboBox *topicName;
    QLineEdit *addNewTopic;
    QPushButton *addTopic;

    QStringList *imageUrls;
    QList<CustomImage *> annotations;
    int currentIndex;

    double zoom;
    double maxZoom;
    double minZoom;

    void createWidgets();
    void initImages();
    void createActions();
    void setImage(int index);

protected:
    void wheelEvent(QWheelEvent *event);

signals:
    void prepared();
    void saved();
    void transitTest(bool);
    void hideEditWidget();
    void transitEdit();

public slots:
    void addNewAnnotation();
    void enableSelect();
    void enableMove();
    void changeCursorDelete();
    void deleteItem();
    void prepare();
    void saveAndExit();
    void exit();
    void previousImage();
    void nextImage();
    void clearScene();
    void refreshScene();
    void saveAndTransitTest();
    void saveAndTransitEdit();
    void newTopic();

};

#endif // LESSONWIDGET_H
