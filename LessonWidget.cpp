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
    annotations = QList<AnnotationGraphicsItem *>();

    /*
     * Push any image url u want here
     */
    //imageUrls->push_back("C:/Program Files/Epic Battles ROTZ/Planets/Earth - 4.5bya");

    zoom = 1.0;
    maxZoom = 3.0;
    minZoom = 0.4;
    createWidgets();
    createActions();
    initImages();
}

void LessonWidget::createWidgets()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topHeader = new QHBoxLayout();
    QHBoxLayout *topLeftHeader = new QHBoxLayout();
    QHBoxLayout *topRightHeader = new QHBoxLayout();
    QHBoxLayout *graphicsLayout = new QHBoxLayout();

    toolbar = new QToolBar(tr("Edit"),this);
    toolbar->setFixedSize(500,50);
    topRightHeader->addWidget(toolbar);

    QLabel *titleLabel = new QLabel(tr("Title : "));
    QLabel *topicLabel = new QLabel(tr("Topic : "));

    lessonName = new QLineEdit();
    lessonName->setFixedSize(220,30);
    lessonName->setMaxLength(50);

    topicName = new QComboBox();
    topicName->setFixedSize(220,30);
    LessonsDB ldb = LessonsDBController::getDB();
    QStringList list = ldb.getTopics();
    topicName->addItems(list);

    topLeftHeader->addWidget(titleLabel);
    topLeftHeader->addWidget(lessonName);
    topLeftHeader->addWidget(topicLabel);
    topLeftHeader->addWidget(topicName);

    graphicsLayout->addWidget(imageView);
    topHeader->addLayout(topLeftHeader);
    topHeader->addLayout(topRightHeader);
    mainLayout->addLayout(topHeader);
    mainLayout->addLayout(graphicsLayout);


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

    toolbar->addAction(selectAction);
    toolbar->addAction(handAction);
    toolbar->addAction(linkAction);
    toolbar->addAction(annotationAction);
    toolbar->addAction(deleteAction);
    toolbar->addAction(imageAction);
    toolbar->addAction(saveAction);
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

void LessonWidget::addNewAnnotation()
{
    int i = annotations.size();
    AnnotationGraphicsItem *agi = new AnnotationGraphicsItem();
    agi->box->setIndex(i);
    agi->boxRect->setIndex(i);
    agi->line->setIndex(i);
    agi->lineRect->setIndex(i);
    scene->addItem(agi->box);
    scene->addItem(agi->line);
    scene->addItem(agi->boxRect);
    scene->addItem(agi->lineRect);

    annotations.push_back(agi);

}

void LessonWidget::enableMove()
{
    QWidget::setCursor(Qt::OpenHandCursor);
    imageView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene->setDelete(false);
    for (int i=0; i<annotations.size(); i++)
    {
        annotations.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable);
        annotations.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable);
        annotations.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable);
        annotations.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void LessonWidget::enableSelect()
{
    imageView->setDragMode(QGraphicsView::RubberBandDrag);
    QWidget::setCursor(Qt::ArrowCursor);
    scene->setDelete(false);
    for (int i=0; i<annotations.size(); i++)
    {
        annotations.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

void LessonWidget::changeCursorDelete()
{
    imageView->setDragMode(QGraphicsView::NoDrag);
    QWidget::setCursor(QCursor(QPixmap(tr(":/assets/delete.png"))));
    scene->setDelete(true);
    for (int i=0; i<annotations.size(); i++)
    {
        annotations.at(i)->box->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->boxRect->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->line->setFlag(QGraphicsItem::ItemIsMovable, false);
        annotations.at(i)->lineRect->setFlag(QGraphicsItem::ItemIsMovable, false);
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

    for (int i=0; i<nums.size(); i++)
    {
        AnnotationGraphicsItem *tempItem = annotations.takeAt(nums.at(i));
        scene->removeItem(tempItem->box);
        scene->removeItem(tempItem->boxRect);
        scene->removeItem(tempItem->line);
        scene->removeItem(tempItem->lineRect);
        delete tempItem;
    }

    for (int i=0; i<annotations.size(); i++)
    {
        AnnotationGraphicsItem *tempItem = annotations.at(i);
        tempItem->box->setIndex(i);
        tempItem->boxRect->setIndex(i);
        tempItem->line->setIndex(i);
        tempItem->lineRect->setIndex(i);
    }
}

void LessonWidget::prepare()
{
    Lesson tempLesson;
    int editIndex = LessonsDBController::getIndex();
    if (editIndex < 0)
    {
        return;
    }
    tempLesson = LessonsDBController::getDB().getLessons().at(editIndex);
    QList<AnnotationGraphicsItem *> tempList = tempLesson.getAnnos();

    for (int i=0; i<tempList.size(); i++)
    {
        AnnotationGraphicsItem *item = tempList.at(i);
        annotations.push_back(item);
        scene->addItem(item->box);
        scene->addItem(item->line);
        scene->addItem(item->boxRect);
        scene->addItem(item->lineRect);
    }
    QStringList list = LessonsDBController::getDB().getTopics();
    for (int i=0; i<list.size(); i++)
    {
        if (list.at(i) == tempLesson.getTopic())
        {
            topicName->setCurrentIndex(i);
        }
    }
    lessonName->setText(tempLesson.getLesson());

    emit prepared();
}

void LessonWidget::saveAndExit()
{
    LessonsDBController::editLesson(LessonsDBController::getIndex(),lessonName->text(),topicName->currentText(),annotations);
    LessonsDBController::setIndex(-1);
    int size = annotations.size();
    for (int i=0; i<size; i++)
    {
        AnnotationGraphicsItem *tempItem = annotations.takeLast();
        scene->removeItem(tempItem->box);
        scene->removeItem(tempItem->boxRect);
        scene->removeItem(tempItem->line);
        scene->removeItem(tempItem->lineRect);
    }
    emit saved();
}

void LessonWidget::exit()
{
    delete this;
}

void LessonWidget::showTestWidget() {
    //testWidget = new TestWidget(STICK THE LESSON NAME HERE);

    // I haven't added any buttons there yet
}
