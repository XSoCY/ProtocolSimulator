#ifndef SYSFAULTTREEMANAGER_H
#define SYSFAULTTREEMANAGER_H

#include "httpresponsemanager_global.h"
#include "httpresponsebase.h"

#include <QObject>
#include <QNetworkReply>
#include <QMap>
#include <QJsonObject>

typedef QMap<int, QJsonObject> SysFaultTreeItems;

class HTTPRESPONSEMANAGERSHARED_EXPORT SysFaultTreeManager : public httpResponseBase
{
    Q_OBJECT
public:
    SysFaultTreeManager(QObject *parent = nullptr);

    bool getSysFaultBySysId(int sysId, SysFaultTreeItems &items);
    bool getSysTreeById(int id, QJsonObject &sysTree);

    bool updateSysFaultTree(const QByteArray &value);
    bool updateSysFaultTree(const QJsonDocument &value);
};

#endif // SYSFAULTTREEMANAGER_H
