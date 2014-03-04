#include "UserDb.h"
#include "User.h"

User UserDb::userWithEmail(const QString &email)
{
    if (email == "teacher") {
        return User("teacher", "mypassword");
    }
    return User();
}