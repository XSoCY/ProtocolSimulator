#ifndef MENUCONTROLMANAGER_H
#define MENUCONTROLMANAGER_H

#include "httpresponsemanager_global.h"
#include "httpresponsebase.h"

#include <QObject>
#include <QNetworkReply>
#include <QMap>
#include <QJsonObject>

class HTTPRESPONSEMANAGERSHARED_EXPORT MenuControlManager : public httpResponseBase
{
public:
    MenuControlManager();
};

#endif // MENUCONTROLMANAGER_H
