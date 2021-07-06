#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "httpresponsemanager_global.h"
#include "httpresponsebase.h"

class HTTPRESPONSEMANAGERSHARED_EXPORT UserManager : public httpResponseBase
{
public:
    UserManager();

    bool userLogin(const QString &name, const QString &password);

    bool registerUser(const QString &name, const QString &password, const QString &desc, int role);
};

#endif // USERMANAGER_H
