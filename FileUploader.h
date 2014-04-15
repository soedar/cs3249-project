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
#include <QTableWidget>
#include <LessonsDBController.h>

class FileUploader : public QWidget
{
    Q_OBJECT
public:
    FileUploader(QWidget *parent);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void addItem(const QString &string);
    QStringList* getList();
    void clearData();
    bool editing;
    int numOriginal;

public slots:
    void deleteItem();
    void prepare(QStringList list);

signals:
    void prepared();

private:
    void refreshGrid();
    QStringList *files;
    QTableWidget *fileTable;
    QList<GridButton *> *grids;
    int maxRows;

};

#endif // FILEUPLOADER_H
