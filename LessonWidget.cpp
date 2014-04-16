#include "LessonWidget.h"

//The lesson widget contains a graphics scene and a graphics view
//You can put any graphics items into the scene and modify them
//in any way.
LessonWidget::LessonWidget()
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


    zoom = 1.0;
    maxZoom = 3.0;
    minZoom = 0.4;
    createWidgets();
    createActions();
}

void LessonWidget::createWidgets()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topHeader = new QHBoxLayout();
    QHBoxLayout *topLeftHeader = new QHBoxLayout();
    QHBoxLayout *topRightHeader = new QHBoxLayout();
    QHBoxLayout *topUpHeader = new QHBoxLayout();
    QVBoxLayout *topicHeader = new QVBoxLayout();
    QHBoxLayout *topDownHeader = new QHBoxLayout();
    QHBoxLayout *graphicsLayout = new QHBoxLayout();

    toolbar = new QToolBar(tr("Edit"),this);
    toolbar->setFixedSize(500,50);
    topRightHeader->addWidget(toolbar);

    QLabel *titleLabel = new QLabel(tr("Title : "));
    QLabel *topicLabel = new QLabel(tr("Topic : "));
    QLabel *addTopicLabel = new QLabel(tr("Add Topic : "));

    lessonName = new QLineEdit();
    lessonName->setFixedSize(180,25);
    lessonName->setMaxLength(40);

    addNewTopic = new QLineEdit();
    addNewTopic->setFixedSize(180,25);
    addNewTopic->setMaxLength(40);

    topicName = new QComboBox();
    topicName->setFixedSize(220,30);

    addTopic = new QPushButton(tr("Add"));
    addTopic->setEnabled(true);

    connect(addTopic,SIGNAL(clicked()),this,SLOT(newTopic()));

    topLeftHeader->addWidget(titleLabel);
    topLeftHeader->addWidget(lessonName);
    topUpHeader->addWidget(addTopicLabel);
    topUpHeader->addWidget(addNewTopic);
    topUpHeader->addWidget(addTopic);
    topDownHeader->addWidget(topicLabel);
    topDownHeader->addWidget(topicName);
    topicHeader->addLayout(topUpHeader);
    topicHeader->addLayout(topDownHeader);
    topLeftHeader->addLayout(topicHeader);

    graphicsLayout->addWidget(imageView);
    topHeader->addLayout(topLeftHeader);
    topHeader->addLayout(topRightHeader);
    mainLayout->addLayout(topHeader);
    mainLayout->addLayout(graphicsLayout);


    connect(scene,SIGNAL(toTheLeft()),this,SLOT(previousImage()));
    connect(scene,SIGNAL(toTheRight()),this,SLOT(nextImage()));


    setLayout(mainLayout);
}

void LessonWidget::createActions()
{
    selectAction = new QAction(tr("&Select"),this);
    selectAction->setIcon(QIcon(":/assets/select.png"));
    selectAction->setShortcut(tr("Ctrl+S"));
    selectAction->setStatusTip(tr("Select items in the scene"));

    connect(selectAction,SIGNAL(triggered()),this,SLOT(enableSelect()));

    handAction = new QAction(tr("&Hand"),this);
    handAction->setIcon(QIcon(":/assets/hand.png"));
    handAction->setShortcut(tr("Ctrl+H"));
    handAction->setStatusTip(tr("For Dragging the scene"));

    connect(handAction, SIGNAL(triggered()),this,SLOT(enableMove()));

    linkAction = new QAction(tr("&Link"), this);
    linkAction->setIcon(QIcon(":/assets/link.png"));
    linkAction->setShortcut(tr("Ctrl+L"));
    linkAction->setStatusTip(tr("Create a link to the notes"));

    annotationAction = new QAction(tr("&Annotation"), this);
    annotationAction->setIcon(QIcon(":/assets/annotate.png"));
    annotationAction->setShortcut(tr("Ctrl+A"));
    annotationAction->setStatusTip(tr("Create a new annotation"));

    connect(annotationAction, SIGNAL(triggered()),this,SLOT(addNewAnnotation()));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setIcon(QIcon(":/assets/delete.png"));
    deleteAction->setShortcut(tr("Ctrl+X"));
    deleteAction->setStatusTip(tr("Delete an item"));

    connect(deleteAction, SIGNAL(triggered()),this,SLOT(changeCursorDelete()));
    connect(scene, SIGNAL(clicked()),this,SLOT(deleteItem()));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setIcon(QIcon(":/assets/save_exit.png"));
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save changes and return to lessons window"));

    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveAndExit()));

    imageAction = new QAction(tr("Manage Images and Files"), this);
    imageAction->setIcon(QIcon(":/assets/notes.png"));
    imageAction->setShortcut(tr("Ctrl+I"));
    imageAction->setStatusTip(tr("Add/Delete images and files for this lesson"));

    connect(imageAction,SIGNAL(triggered()),this,SLOT(saveAndTransitEdit()));

    testAction = new QAction(tr("Self-Test"), this);
    testAction->setIcon(QIcon(":/assets/test.png"));
    testAction->setShortcut(tr("Ctrl+T"));
    testAction->setStatusTip(tr("Go to the test editor for this lesson"));

    connect(testAction,SIGNAL(triggered()),this,SLOT(saveAndTransitTest()));

    toolbar->addAction(selectAction);
    toolbar->addAction(handAction);
    toolbar->addAction(linkAction);
    toolbar->addAction(annotationAction);
    toolbar->addAction(deleteAction);
    toolbar->addAction(imageAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(testAction);
}

void LessonWidget::setImage(int index)
{
    QPixmap pixmap = QPixmap::fromImage(QImage(imageUrls->at(index)));
    image->setPixmap(pixmap);
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

void LessonWidget::addNewAnnotation()
{
    if (annotations.size() < 1)
    {
        return;
    }
    int i = annotations.at(currentIndex)->getAnnos().size();
    AnnotationGraphicsItem *agi = new AnnotationGraphicsItem();
    agi->box->setIndex(i);
    agi->boxRect->setIndex(i);
    agi->line->setIndex(i);
    agi->lineRect->setIndex(i);
    scene->addItem(agi->box);
    scene->addItem(agi->line);
    scene->addItem(agi->boxRect);
    scene->addItem(agi->lineRect);

    qDebug() << "Anno size : " << annotations.at(currentIndex)->getAnnos().size() << "\n";
    annotations.at(currentIndex)->addAnno(agi);
    qDebug() << "Anno size : " << annotations.at(currentIndex)->getAnnos().size() << "\n";
}

void LessonWidget::enableMove()
{
    QWidget::setCursor(Qt::OpenHandCursor);
    imageView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene->setDelete(false);
    QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<tempList.size(); i++)
    {
        tempList.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable);
        tempList.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable);
        tempList.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable);
        tempList.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void LessonWidget::enableSelect()
{
    imageView->setDragMode(QGraphicsView::RubberBandDrag);
    QWidget::setCursor(Qt::ArrowCursor);
    scene->setDelete(false);
    QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<tempList.size(); i++)
    {
        tempList.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

void LessonWidget::changeCursorDelete()
{
    imageView->setDragMode(QGraphicsView::NoDrag);
    QWidget::setCursor(QCursor(QPixmap(tr(":/assets/delete.png"))));
    scene->setDelete(true);
    QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<tempList.size(); i++)
    {
        tempList.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable, false);
        tempList.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

void LessonWidget::deleteItem()
{
    QList<QGraphicsItem *> list;
    QList<int> nums;
    list = scene->selectedItems();

    for (int i=0; i<list.size(); i++)
    {
        CustomText *textItem = (CustomText *)(list.at(i));
        int var = textItem->getIndex();
        nums.push_back(var);
    }

    qSort(nums.begin(),nums.end(),qGreater<int>());

    QList<AnnotationGraphicsItem *> tempList = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<nums.size(); i++)
    {
        AnnotationGraphicsItem *tempItem = tempList.takeAt(nums.at(i));
        scene->removeItem(tempItem->box);
        scene->removeItem(tempItem->boxRect);
        scene->removeItem(tempItem->line);
        scene->removeItem(tempItem->lineRect);
        annotations.at(currentIndex)->removeAnno(nums.at(i));
        delete tempItem;
    }

    annotations.at(currentIndex)->updateIndices();
}

void LessonWidget::prepare()
{
    Lesson tempLesson;
    int editIndex = LessonsDBController::getIndex();
    if (editIndex < 0)
    {
        return;
    }
    tempLesson = LessonsDBController::getDB()->getLessons().at(editIndex);
    annotations = tempLesson.getAnnos();

    QStringList tempImages = tempLesson.getImageList();

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


    //Initialize topics
    QStringList list = LessonsDBController::getDB()->getTopics();
    topicName->addItems(list);
    for (int i=0; i<list.size(); i++)
    {
        if (list.at(i) == tempLesson.getTopic())
        {
            topicName->setCurrentIndex(i);
        }
    }
    //Initialize lesson name
    lessonName->setText(tempLesson.getLesson());

    qDebug() << "Lesson Loaded\n" << "No.of images = " << annotations.size() << "\n";

    emit prepared();
}

void LessonWidget::saveAndExit()
{
    qDebug() << "Editing Index : " << LessonsDBController::getIndex() << "\n";
    LessonsDBController::editLesson(LessonsDBController::getIndex(),lessonName->text(),topicName->currentText(),annotations);
    LessonsDBController::setIndex(-1);

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
    addNewTopic->clear();
    if (imageUrls->size() > 0)
    {
       scene->removeItem(image);
    }
    imageUrls->clear();
    annotations.clear();

    emit saved();
}

void LessonWidget::saveAndTransitTest()
{
    qDebug() << "Editing Index : " << LessonsDBController::getIndex() << "\n";
    LessonsDBController::editLesson(LessonsDBController::getIndex(),lessonName->text(),topicName->currentText(),annotations);

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
    addNewTopic->clear();
    if (imageUrls->size() > 0)
    {
       scene->removeItem(image);
    }
    imageUrls->clear();
    annotations.clear();

    emit transitTest();
}

void LessonWidget::saveAndTransitEdit()
{
    qDebug() << "Editing Index : " << LessonsDBController::getIndex() << "\n";
    LessonsDBController::editLesson(LessonsDBController::getIndex(),lessonName->text(),topicName->currentText(),annotations);

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
    addNewTopic->clear();
    if (imageUrls->size() > 0)
    {
       scene->removeItem(image);
    }
    imageUrls->clear();
    annotations.clear();

    emit transitEdit();
}


void LessonWidget::exit()
{
    delete this;
}

void LessonWidget::showTestWidget() {
    //testWidget = new TestWidget(STICK THE LESSON NAME HERE);

    // I haven't added any buttons there yet
}

void LessonWidget::previousImage()
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
void LessonWidget::nextImage()
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

void LessonWidget::clearScene()
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


void LessonWidget::refreshScene()
{
    qDebug() << "CI : " << currentIndex << "\n";
    setImage(currentIndex);
    QList<AnnotationGraphicsItem *> tempAnnos = annotations.at(currentIndex)->getAnnos();
    for (int i=0; i<tempAnnos.size(); i++)
    {
        AnnotationGraphicsItem *anno = tempAnnos.at(i);
        scene->addItem(anno->line);
        scene->addItem(anno->lineRect);
        scene->addItem(anno->boxRect);
        scene->addItem(anno->box);
    }
}

void LessonWidget::newTopic()
{
    if (addNewTopic->text().length() > 0)
    {
        LessonsDBController::addTopic(addNewTopic->text());
        LessonsDB *ldb = LessonsDBController::getDB();
        QString string = topicName->currentText();
        QStringList list = ldb->getTopics();
        topicName->clear();
        topicName->addItems(list);
        for (int i=0; i<list.size(); i++)
        {
            if (list.at(i) == string)
            {
                topicName->setCurrentIndex(i);
            }
        }
        addNewTopic->clear();
    }
}
