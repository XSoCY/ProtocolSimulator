#ifndef HTTPRESPONSEMANAGER_H
#define HTTPRESPONSEMANAGER_H

#include "httpresponsemanager_global.h"
#include "Json.h"

#include <QObject>

class HTTPRESPONSEMANAGERSHARED_EXPORT HttpResponseManager
{

public:
    static HttpResponseManager *getInstance()
    {
        if( !m_instance ) m_instance = new HttpResponseManager;

        return m_instance;
    }

    void setHttpPathBase(const QString &url);
    QString getHttpPathBase();

    void setToken(const QString &token);
    QString getToken();

    void setUserObject(const QJsonObject &userInfo);
    QJsonObject getUserObject();

private:
    HttpResponseManager();

    static HttpResponseManager *m_instance;

    QString                     m_httpPathBase;
    QString                     m_token;

    QJsonObject                 m_userObject;
};

#endif // HTTPRESPONSEMANAGER_H
