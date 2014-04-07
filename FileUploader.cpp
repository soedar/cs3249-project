#include "FileUploader.h"
#include "qdebug.h"

FileUploader::FileUploader(QWidget *parent)
    :QWidget(parent)
{
    setFixedSize(300,350);
    setAcceptDrops(true);
    files = new QStringList();
    fileGrid = new QGridLayout();
    grids = new QList<GridButton *>();
    setLayout(fileGrid);
    maxRows = 4;
    maxCols = 3;
}
void FileUploader::addItem(const QString &string)
{
    files->push_back(string);
    QStringList list = string.split("/");
    GridButton *button = new GridButton(this);
    button->setIcon(QIcon(":/assets/pdf.png"));
    button->setText(tr(list.last().toStdString().c_str()));
    button->setIndex(grids->count());
    button->setEnabled(true);
    fileGrid->addWidget(button, grids->count()/maxCols , grids->count()%maxCols);
    grids->push_back(button);
    connect(button,SIGNAL(rightClicked()),this, SLOT(deleteItem()));
}

void FileUploader::deleteItem()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();

    qDebug("Sender's index : ");
    qDebug() << index;
    qDebug("\n");
    qDebug("Grids Size Now : ");
    qDebug() << grids->count();
    qDebug("\n");
    files->removeAt(index);
    grids->removeAt(index);
    fileGrid->removeWidget(button);

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

QStringList* FileUploader::getList()
{
    return files;
}

void FileUploader::refreshGrid()
{
    for (int i=0; i<grids->count(); i++)
    {
        fileGrid->removeWidget(grids->at(i));
    }
    for (int i=0; i<grids->count(); i++)
    {
        fileGrid->addWidget(grids->at(i), i/maxCols , i%maxCols);
    }
}

void FileUploader::clearData()
{
    for (int i=0; i<grids->count(); i++)
    {
        fileGrid->removeWidget(grids->at(i));
    }
    files->clear();
    grids->clear();
}


/**
 * Below 4 functions taken from
 * http://qt-project.org/wiki/Drag_and_Drop_of_files
 * Copyright (c) 2011, Gerolf Reinwardt. All rights reserved.
 */


void FileUploader::dragEnterEvent(QDragEnterEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void FileUploader::dragMoveEvent(QDragMoveEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}


void FileUploader::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void FileUploader::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QString string = urlList.at(i).toLocalFile();

            if (files->contains(string))
            {
                qDebug("It seems you have already dragged this file here.\n");
            }
            else
            {
                if (files->count() >= maxRows*maxCols)
                {
                    qDebug("Way too many files already\n");
                }
                else
                {
                    if (string.contains(".pdf"))
                    {
                        addItem(string);
                    }
                    else
                    {
                        qDebug("Item u dragged is not a pdf file");
                    }
                }
            }
        }

    }
}
