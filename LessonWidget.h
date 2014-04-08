#ifndef LESSONWIDGET_H
#define LESSONWIDGET_H

#include <QDialog>
#include <QGraphicsView>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <LessonsDBController.h>
#include <QPixmap>
#include <QWheelEvent>
#include <CustomText.h>

class LessonWidget : public QDialog
{
    Q_OBJECT
public:
    LessonWidget();

private:
    QGraphicsView *imageView;
    QGraphicsScene *scene;
    QPixmap image;
    QTextEdit *pdfView;
    QMenu *editMenu;
    QMenu *transitMenu;
    QAction *selectAction;
    QAction *handAction;
    QAction *linkAction;
    QAction *annotationAction;
    QAction *deleteAction;
    QAction *imageAction;

    QStringList *imageUrls;

    double zoom;
    double maxZoom;
    double minZoom;

    void createWidgets();
    void initImages();
    void setImage(int index);

protected:
    //void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    //void resizeEvent(QResizeEvent *event);
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void mouseReleaseEvent(QMouseEvent *event);
    //virtual void mouseMoveEvent(QMouseEvent *event);


signals:

public slots:

};

#endif // LESSONWIDGET_H
