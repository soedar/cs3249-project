#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QWidget>
#include <QStringList>
#include <QGridLayout>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <GridButton.h>

class ImageUploader : public QWidget
{
    Q_OBJECT
public:
    ImageUploader(QWidget *parent);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void addItem(const QString &string);
    QStringList* getList();
    void clearData();

public slots:
    void deleteItem();

private:
    void refreshGrid();
    QStringList *images;
    QGridLayout *imageGrid;
    QList<GridButton *> *grids;
    int maxRows;
    int maxCols;

};

#endif // IMAGEUPLOADER_H
