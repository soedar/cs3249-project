#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <QString>
#include <QMap>
#include "User.h"

class DatabaseLayer {
public:
    DatabaseLayer();
    User userWithEmail(const QString &);

private:
    QString dataPath;
    QMap<QString, User> users;

    void loadAllUsers();
    void preloadUsers();
    QString userDatabaseFile();
};

#endif
