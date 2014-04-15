#include "ImageUploader.h"
#include <QHeaderView>
#include "qdebug.h"

//A custom widget that allows u to drag and drop images onto it.
ImageUploader::ImageUploader(QWidget *parent)
: QWidget(parent)
{
    setFixedSize(300,350);
    setAcceptDrops(true);
    images = new QStringList();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    imageTable = new QTableWidget();
    mainLayout->addWidget(imageTable);
    grids = new QList<GridButton *>();
    setLayout(mainLayout);
    maxRows = 50;
    QStringList headers;
    headers << "images";
    imageTable->setColumnCount(1);
    imageTable->setHorizontalHeaderLabels(headers);
    QHeaderView *tempHeader = imageTable->horizontalHeader();
    tempHeader->setResizeMode(0, QHeaderView::Stretch);
    imageTable->setRowCount(0);
    editing = false;
    numOriginal = 0;
}

void ImageUploader::addItem(const QString &string)
{
    images->push_back(string);
    QStringList list = string.split("/");
    GridButton *button = new GridButton(this);
    button->setIconSize(QSize(36,36));
    button->setFixedSize(260,80);
    button->setIcon(QIcon(":/assets/pdf.png"));
    button->setText(tr(list.last().toStdString().c_str()));
    button->setIndex(grids->count());
    button->setEnabled(true);
    imageTable->insertRow(imageTable->rowCount());
    imageTable->setRowHeight(imageTable->rowCount()-1,80);
    imageTable->setCellWidget(imageTable->rowCount()-1, 0, button);
    grids->push_back(button);
    connect(button, SIGNAL(rightClicked()), this, SLOT(deleteItem()));
}

void ImageUploader::deleteItem()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();

    images->removeAt(index);
    grids->removeAt(index);
    imageTable->removeCellWidget(index,0);
    imageTable->removeRow(index);

    if (editing)
    {
        if (index < numOriginal)
        {
            LessonsDBController::destroyCI(LessonsDBController::getIndex(),index);
            numOriginal--;
        }
    }

    for (int i=0; i<grids->count(); i++)
    {
        grids->at(i)->setIndex(i);
    }

    delete button;

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
        imageTable->removeCellWidget(imageTable->rowCount()-1 , 0);
        imageTable->removeRow(imageTable->rowCount()-1);
        GridButton *tempButton = grids->takeLast();
        delete tempButton;

    }
    images->clear();
    grids->clear();
    editing = false;
    numOriginal = 0;
}

void ImageUploader::prepare(QStringList list)
{
    for (int i=0; i<list.size(); i++)
    {
        addItem(list.at(i));
    }
    editing = true;
    numOriginal = list.size();
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
                if (images->count() >= maxRows)
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
