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

    QAction *selectAction;
    QAction *handAction;
    QAction *linkAction;
    QAction *annotationAction;
    QAction *deleteAction;
    QAction *imageAction;
    QAction *saveAction;

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
    //void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    //void resizeEvent(QResizeEvent *event);
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void mouseReleaseEvent(QMouseEvent *event);
    //virtual void mouseMoveEvent(QMouseEvent *event);


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
