#include "ImageUploader.h"

ImageUploader::ImageUploader()
{
    images = new QStringList();
    imageGrid = new QGridLayout();
    grids = new QList<GridItem>();

}

void ImageUploader::deleteItem(const QString &string)
{
    int index = images->indexOf(string,0);

    if (index != -1)
    {
        images->removeAt(index);
        imageGrid->removeWidget(grids->at(index));
        grids->removeAt(index);
    }
}

void ImageUploader::addItem(const QString &string)
{
    images->push_back(string);
    GridItem tempItem = GridItem();
    tempItem.setLabel(string);
    grids->push_back(tempItem);
    imageGrid->addWidget(tempItem);
    connect(tempItem.getButton(),SIGNAL(clicked()),this,deleteItem(string));
}

//Taken from http://qt-project.org/wiki/Drag_and_Drop_of_files
//Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
void ImageUploader::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

//Taken from http://qt-project.org/wiki/Drag_and_Drop_of_files
//Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
void ImageUploader::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

//Taken from http://qt-project.org/wiki/Drag_and_Drop_of_files
//Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
void ImageUploader::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

//Taken from http://qt-project.org/wiki/Drag_and_Drop_of_files
//Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
void ImageUploader::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QString tempString = urlList.at(i).toLocalFile();
            if (images->contains(tempString))
            {
                qDebug("It seems you have already dragged this file?\n");
            }
            else
            {
                if (tempString.contains(".png") || tempString.contains(".jpg") || tempString.contains(".jpeg") || tempString.contains(".gif"))
                {
                    addItem(urlList.at(i).toLocalFile());
                }
                else
                {
                    qDebug("File is not an image\n");
                }
            }
        }

    }

}
