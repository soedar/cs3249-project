#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QWidget>
#include <QStringList>
#include <QGridLayout>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QList>
#include "GridItem.h"

class ImageUploader : public QWidget
{
    Q_OBJECT
public:
    ImageUploader();
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void addItem(const QString &string);

public slots:
    void deleteItem(const QString &string);

private:
    QStringList *images;
    QGridLayout *imageGrid;
    QList<GridItem> *grids;

signals:

public slots:

};

#endif // IMAGEUPLOADER_H
