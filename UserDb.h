#ifndef USER_DB_H
#define USER_DB_H

#include <QString>

class User;

class UserDb {
private:
    UserDb();

public:
    static User userWithEmail(const QString &);
};

#endif