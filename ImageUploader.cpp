#include "ImageUploader.h"
#include "qdebug.h"

ImageUploader::ImageUploader(QWidget *parent)
: QWidget(parent)
{
    setFixedSize(300,350);
    setAcceptDrops(true);
    images = new QStringList();
    imageGrid = new QGridLayout();
    grids = new QList<GridButton *>();
    setLayout(imageGrid);
    maxRows = 4;
    maxCols = 3;
}

void ImageUploader::addItem(const QString &string)
{
    images->push_back(string);
    QStringList list = string.split("/");
    GridButton *button = new GridButton(this);
    button->setIconSize(QSize(48,48));
    button->setIcon(QIcon(":/assets/diagrams.png"));
    button->setText(tr(list.last().toStdString().c_str()));
    button->setIndex(grids->count());
    button->setEnabled(true);
    imageGrid->addWidget(button, grids->count()/maxCols , grids->count()%maxCols);
    grids->push_back(button);
    connect(button,SIGNAL(rightClicked()),this, SLOT(deleteItem()));
}

void ImageUploader::deleteItem()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();

    qDebug("Sender's index : ");
    qDebug() << index;
    qDebug("\n");
    qDebug("Grids Size Now : ");
    qDebug() << grids->count();
    qDebug("\n");
    images->removeAt(index);
    grids->removeAt(index);
    imageGrid->removeWidget(button);

    for (int i=0; i<grids->count(); i++)
    {
        grids->at(i)->setIndex(i);
    }

    qDebug("Grids Size After : ");
    qDebug() << grids->count();
    qDebug("\n");

    delete button;

    refreshGrid();
    //button->exit();
}

void ImageUploader::refreshGrid()
{
    for (int i=0; i<grids->count(); i++)
    {
        imageGrid->removeWidget(grids->at(i));
    }
    for (int i=0; i<grids->count(); i++)
    {
        imageGrid->addWidget(grids->at(i), i/maxCols , i%maxCols);
    }
}

QStringList* ImageUploader::getList()
{
    return images;
}

void ImageUploader::clearData()
{
    int size = grids->count();
    for (int i=0; i<size; i++)
    {
        imageGrid->removeWidget(grids->last());
        GridButton *tempButton = grids->takeLast();
        delete tempButton;
    }
    images->clear();
    grids->clear();
}

/**
 * Below 4 functions taken from
 * http://qt-project.org/wiki/Drag_and_Drop_of_files
 * Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
 */


void ImageUploader::dragEnterEvent(QDragEnterEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void ImageUploader::dragMoveEvent(QDragMoveEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}


void ImageUploader::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

//Modified to accomodate this program
void ImageUploader::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QString string = urlList.at(i).toLocalFile();

            if (images->contains(string))
            {
                qDebug("It seems you have already dragged this file here.\n");
            }
            else
            {
                if (images->count() >= maxRows*maxCols)
                {
                    qDebug("Way too many images already\n");
                }
                else
                {
                    if (string.contains(".png") || string.contains(".jpg") || string.contains(".jpeg") || string.contains(".gif") || string.contains(".bmp"))
                    {
                        addItem(string);
                    }
                    else
                    {
                        qDebug("Item u dragged is not an image");
                    }
                }
            }
        }

    }
}
