#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <QString>
#include <QMap>
#include "User.h"
#include "LessonsDBController.h"

class DatabaseLayer {

public:
    DatabaseLayer();
    User userWithEmail(const QString &);
    LessonsDBController *ldb;


private:
    QString dataPath;
    //QString lessonsDataPath;
    QMap<QString, User> users;



    void loadAllUsers();
    void preloadUsers();
    QString userDatabaseFile();
    QString lessonsDatabaseFile();

public:
    void saveLessons();
    void loadLessons();

};

#endif
