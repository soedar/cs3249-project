#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

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

class FileUploader : public QWidget
{
public:
    FileUploader(QWidget *parent);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void addItem(const QString &string);
    QStringList* getList();
    void clearData();

public slots:
    void deleteItem();//const QString &string);

private:
    void refreshGrid();
    QStringList *files;
    QGridLayout *fileGrid;
    QList<GridButton *> *grids;
    int maxRows;
    int maxCols;
};

#endif // FILEUPLOADER_H
