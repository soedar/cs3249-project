#include "LessonWidget.h"

LessonWidget::LessonWidget()
{
    setGeometry(0,0,1000,600);
    imageView = new QGraphicsView(this);
    imageView->setGeometry(50,50,900,500);
    imageView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene = new QGraphicsScene(this);
    //pdfView = new QTextEdit(this);
    imageView->setScene(scene);
    imageUrls = new QStringList();

    /*
     * Push any image url u want here
     */
    //imageUrls->push_back("C:/Program Files/Epic Battles ROTZ/Planets/Earth - 4.5bya");

    zoom = 1.0;
    maxZoom = 10.0;
    minZoom = 0.1;
    createWidgets();
    initImages();
}

void LessonWidget::createWidgets()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topHeader = new QHBoxLayout();
    QHBoxLayout *graphicsLayout = new QHBoxLayout();

    graphicsLayout->addWidget(imageView);
    mainLayout->addLayout(topHeader);
    mainLayout->addLayout(graphicsLayout);

    CustomText *tempText = new CustomText();
    CustomCircle *boxCircle = new CustomCircle();
    CustomCircle *lineCircle = new CustomCircle();
    CustomLine *line = new CustomLine();

    connect(tempText,SIGNAL(moved(QPointF)),boxCircle,SLOT(recieveChange(QPointF)));
    connect(tempText,SIGNAL(movedForLine(QPointF)),line,SLOT(setPos1(QPointF)));
    connect(boxCircle,SIGNAL(moved(QPointF)),tempText,SLOT(recieveChange(QPointF)));
    connect(lineCircle,SIGNAL(moved(QPointF)),line,SLOT(setPos2(QPointF)));
    connect(boxCircle,SIGNAL(moved(QPointF)),line,SLOT(setPos1(QPointF)));

    scene->addItem(tempText);
    scene->addItem(line);
    scene->addItem(boxCircle);
    scene->addItem(lineCircle);

    tempText->setPos(10,50);
    boxCircle->setPos(10,110);
    lineCircle->setPos(10,150);
    line->setPos1(QPoint(10,110));
    line->setPos2(QPoint(10,150));

    setLayout(mainLayout);
}

void LessonWidget::initImages()
{
    if (imageUrls->size() > 0)
    {
        setImage(0);
    }
}
void LessonWidget::setImage(int index)
{
    image = QPixmap::fromImage(QImage(imageUrls->at(index)));

    scene->addPixmap(image);
}

void LessonWidget::wheelEvent(QWheelEvent *event)
{
    imageView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        // Scale the view / do the zoom
        double scaleFactor = 0.1;

        double scaleTarget;

        if(event->delta() > 0)
        {
            if (zoom+scaleFactor <= maxZoom)
            {
                scaleTarget = zoom+scaleFactor;
            }
            // Zoom in
            imageView->scale(scaleTarget/zoom, scaleTarget/zoom);
            zoom = scaleTarget;
        }
        else
        {
            if (zoom-scaleFactor >= minZoom)
            {
                scaleTarget = zoom-scaleFactor;
            }
            // Zooming out
            imageView->scale(scaleTarget/zoom, scaleTarget/zoom);
            zoom = scaleTarget;
        }

        // Don't call superclass handler here
        // as wheel is normally used for moving scrollbars
}
