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
#include <AnnotationGraphicsItem.h>
#include <CustomScene.h>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class LessonWidget : public QDialog
{
    Q_OBJECT
public:
    LessonWidget();

private:
    QGraphicsView *imageView;
    CustomScene *scene;
    QPixmap image;
    QTextEdit *pdfView;
    QMenu *transitMenu;
    QToolBar *toolbar;

    QAction *selectAction; //Disables Movement, Enables Multi-Selection
    QAction *handAction; // Enables Movement, Disables Multi-Selection
    QAction *linkAction; //NOT IMPLEMENTED
    QAction *annotationAction; //Adds a new annotation to a predefined spot in the scene
    QAction *deleteAction; //Click once to change icon, click again to select an item, click again to delete selected items
    QAction *imageAction; //NOT IMPLEMENTED
    QAction *saveAction; //Saves and exits, working for now

    QLineEdit *lessonName;
    QComboBox *topicName;

    QStringList *imageUrls;
    QList<AnnotationGraphicsItem *> annotations;

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

public slots:
    void addNewAnnotation();
    void enableSelect();
    void enableMove();
    void changeCursorDelete();
    void deleteItem();
    void prepare();
    void saveAndExit();

};

#endif // LESSONWIDGET_H