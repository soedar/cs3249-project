#include "FileUploader.h"
#include <QHeaderView>
#include "qdebug.h"

//A custom widget that allows u to drag and drop files onto it.
FileUploader::FileUploader(QWidget *parent)
:QWidget(parent)
{
    setFixedSize(300,350);
    setAcceptDrops(true);
    files = new QStringList();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    fileTable = new QTableWidget();
    mainLayout->addWidget(fileTable);
    grids = new QList<GridButton *>();
    setLayout(mainLayout);
    maxRows = 50;
    QStringList headers;
    headers << "Files";
    fileTable->setColumnCount(1);
    fileTable->setHorizontalHeaderLabels(headers);
    QHeaderView *tempHeader = fileTable->horizontalHeader();
    tempHeader->setResizeMode(0, QHeaderView::Stretch);
    fileTable->setRowCount(0);
    editing = false;
    numOriginal = 0;

}

void FileUploader::addItem(const QString &string)
{
    files->push_back(string);
    QStringList list = string.split("/");
    GridButton *button = new GridButton(this);
    button->setIconSize(QSize(36,36));
    button->setFixedSize(260,80);
    button->setIcon(QIcon(":/assets/pdf.png"));
    button->setText(tr(list.last().toStdString().c_str()));
    button->setIndex(grids->count());
    button->setEnabled(true);
    fileTable->insertRow(fileTable->rowCount());
    fileTable->setRowHeight(fileTable->rowCount()-1,80);
    fileTable->setCellWidget(fileTable->rowCount()-1, 0, button);
    grids->push_back(button);
    connect(button, SIGNAL(rightClicked()), this, SLOT(deleteItem()));
}

void FileUploader::deleteItem()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();

    files->removeAt(index);
    grids->removeAt(index);
    fileTable->removeCellWidget(index,0);
    fileTable->removeRow(index);

    /*if (editing)
    {
        if (index < numOriginal)
        {
            LessonsDBController::destroyCI(LessonsDBController::getIndex(),index);
            numOriginal--;
        }
    }*/

    for (int i=0; i<grids->count(); i++)
    {
        grids->at(i)->setIndex(i);
    }

    delete button;

}

QStringList* FileUploader::getList()
{
    return files;
}

void FileUploader::clearData()
{
    int size = grids->count();
    for (int i=0; i<size; i++)
    {
        fileTable->removeCellWidget(fileTable->rowCount()-1 , 0);
        fileTable->removeRow(fileTable->rowCount()-1);
        GridButton *tempButton = grids->takeLast();
        delete tempButton;

    }
    files->clear();
    grids->clear();
    editing = false;
    numOriginal = 0;
}

void FileUploader::prepare(QStringList list)
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

//Modified from original code to fit needs of this program
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
                if (files->count() >= maxRows)
                {
                    qDebug("Way too many files already\n");
                }
                else
                {
                    if (string.contains(".htm"))
                    {
                        addItem(string);
                    }
                    else
                    {
                        qDebug("Item u dragged is not a html file");
                    }
                }
            }
        }

    }
}
