#include "StudentLessonWidget.h"

StudentLessonWidget::StudentLessonWidget()
{
    setGeometry(0,0,1000,600);
    imageView = new QGraphicsView(this);
    imageView->setGeometry(50,100,900,500);
    imageView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene = new CustomScene(this);
    //pdfView = new QTextEdit(this);
    imageView->setScene(scene);
    imageUrls = new QStringList();
    annotations = QList<CustomImage *>();
    currentIndex = -1;
    image = new QGraphicsPixmapItem();
    image->setFlag(QGraphicsItem::ItemIsSelectable, false);

<<<<<<< HEAD

    zoom = 1.0;
    maxZoom = 3.0;
    minZoom = 0.4;
    createWidgets();

}

void StudentLessonWidget::createWidgets()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topHeader = new QHBoxLayout();
    QHBoxLayout *graphicsLayout = new QHBoxLayout();

    QLabel *titleLabel = new QLabel(tr("Title : "));
    QLabel *topicLabel = new QLabel(tr("Topic : "));

    lessonName = new QLabel();

    topicName = new QLabel();
=======
    qDebug() << "filelist" << lesson->getFileList();

    textEditWidget = new QTextEdit;
    textEditWidget->setReadOnly(true);

    QStringList fileList = lesson->getFileList();

    if (fileList.count() == 0) {
        textEditWidget->setHtml("<h2>No notes for this lesson</h2>");
    } else {
        QFile htmlFile(fileList.at(0));

        if (!htmlFile.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error", htmlFile.errorString());
            return;
        }

        QString html("");
        QTextStream in(&htmlFile);
        while (!in.atEnd()) {
            html += in.readLine();
        }

        textEditWidget->setHtml(html);
    }


    mainLayout->addWidget(textEditWidget);

    mainLayout->addWidget(new QTextEdit);

    setLayout(mainLayout);
>>>>>>> 347624bff9bef64796a330839e19741b16119093

    topHeader->addWidget(titleLabel);
    topHeader->addWidget(lessonName);
    topHeader->addWidget(topicLabel);
    topHeader->addWidget(topicName);

    graphicsLayout->addWidget(imageView);;
    mainLayout->addLayout(topHeader);
    mainLayout->addLayout(graphicsLayout);

    connect(scene,SIGNAL(toTheLeft()),this,SLOT(previousImage()));
    connect(scene,SIGNAL(toTheRight()),this,SLOT(nextImage()));

    setLayout(mainLayout);
    this->menuWidget = new MenuWidget(this, lesson);
<<<<<<< HEAD

=======
    this->menuWidget->show();
>>>>>>> 347624bff9bef64796a330839e19741b16119093
}



void StudentLessonWidget::resizeEvent(QResizeEvent *event) 
{
    this->menuWidget->adjustSize();
}

void StudentLessonWidget::setImage(int index)
{
    QPixmap pixmap = QPixmap::fromImage(QImage(imageUrls->at(index)));
    image->setPixmap(pixmap);
}

void StudentLessonWidget::prepare(Lesson *less)
{
    lesson = less;
    annotations = lesson->getAnnos();

    QStringList tempImages = lesson->getImageList();

    //Push the images of the lesson into the imageList
    for (int i=0; i<tempImages.size(); i++)
    {
        imageUrls->push_back(tempImages.at(i));
    }

    if (imageUrls->size() > 0)
    {
        scene->addItem(image);
    }

    //Add the annotations of the image at index 0 into the scene
    if (annotations.size() > 0)
    {
        currentIndex = 0;
        setImage(0);
        QList<AnnotationGraphicsItem *> tempAnnos = annotations.at(0)->getAnnos();
        for (int i=0; i<tempAnnos.size(); i++)
        {
            AnnotationGraphicsItem *anno = tempAnnos.at(i);
            scene->addItem(anno->line);
            scene->addItem(anno->lineRect);
            scene->addItem(anno->boxRect);
            scene->addItem(anno->box);
        }
    }
    else
    {
        currentIndex = -1;
    }

    topicName->setText(lesson->getTopic());
    lessonName->setText(lesson->getLesson());

    qDebug() << "Lesson Loaded\n" << "No.of images = " << annotations.size() << "\n";
    //this->menuWidget->show();
    emit prepared();
}

void StudentLessonWidget::previousImage()
{
    qDebug() << "TO THE LEFT! TO THE LEFT!\n";

    if (annotations.size() == 0 || currentIndex == 0)
    {
        return;
    }

    else
    {
        clearScene();
        currentIndex = currentIndex-1;
        refreshScene();
    }
}
void StudentLessonWidget::nextImage()
{
    qDebug() << "TO THE RIGHT! TO THE RIGHT!\n";
    if (annotations.size() == 0 || currentIndex == annotations.size()-1)
    {
        return;
    }
    else
    {
        clearScene();
        currentIndex = currentIndex+1;
        refreshScene();
    }
}

void StudentLessonWidget::clearScene()
{
    qDebug() << "CI : " << currentIndex << "\n";
        QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
        int size = tempList.size();
        for (int i=0; i<size; i++)
        {
            AnnotationGraphicsItem *tempItem = tempList.at(i);
            scene->removeItem(tempItem->box);
            scene->removeItem(tempItem->boxRect);
            scene->removeItem(tempItem->line);
            scene->removeItem(tempItem->lineRect);
        }
}

void StudentLessonWidget::refreshScene()
{
    qDebug() << "CI : " << currentIndex << "\n";
    setImage(currentIndex);
    QList<AnnotationGraphicsItem *> tempAnnos = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<tempAnnos.size(); i++)
    {
        AnnotationGraphicsItem *anno = tempAnnos.at(i);
        anno->line->setFlag(QGraphicsItem::ItemIsMovable,false);
        anno->lineRect->setFlag(QGraphicsItem::ItemIsMovable,false);
        //anno->box->setFlag(QGraphicsItem::ItemIsMovable,false);
        //anno->box->setFlag(QGraphicsItem::ItemIsSelectable,false);
        //anno->boxRect->setFlag(QGraphicsItem::ItemIsMovable,false);
        anno->box->setTextInteractionFlags(Qt::NoTextInteraction);
        scene->addItem(anno->line);
        scene->addItem(anno->lineRect);
        scene->addItem(anno->boxRect);
        scene->addItem(anno->box);

    }
}

void StudentLessonWidget::wheelEvent(QWheelEvent *event)
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

void StudentLessonWidget::exit()
{
    if (annotations.size() > 0)
    {
        QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
        int size = tempList.size();
        for (int i=0; i<size; i++)
        {
            AnnotationGraphicsItem *tempItem = tempList.takeLast();
            scene->removeItem(tempItem->box);
            scene->removeItem(tempItem->boxRect);
            scene->removeItem(tempItem->line);
            scene->removeItem(tempItem->lineRect);
        }
    }
    lessonName->clear();
    topicName->clear();
    if (imageUrls->size() > 0)
    {
       scene->removeItem(image);
    }
    imageUrls->clear();
    annotations.clear();
    //this->menuWidget->hide();
    emit logOut();
}
void StudentLessonWidget::transit()
{
    if (annotations.size() > 0)
    {
        QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
        int size = tempList.size();
        for (int i=0; i<size; i++)
        {
            AnnotationGraphicsItem *tempItem = tempList.takeLast();
            scene->removeItem(tempItem->box);
            scene->removeItem(tempItem->boxRect);
            scene->removeItem(tempItem->line);
            scene->removeItem(tempItem->lineRect);
        }
    }
    lessonName->clear();
    topicName->clear();
    if (imageUrls->size() > 0)
    {
       scene->removeItem(image);
    }
    imageUrls->clear();
    annotations.clear();
    //this->menuWidget->hide();
    emit transitLessons();
}
