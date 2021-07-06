#include "usermanager.h"
#include "httpresponsemanager.h"
#include "json.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QJsonArray>

UserManager::UserManager()
{
    m_relativePath = "phm/user/UserController/";
}

bool UserManager::userLogin(const QString &name, const QString &password)
{
    bool bret = false;

    QString url = HttpResponseManager::getInstance()->getHttpPathBase();
    url += m_relativePath;
    url += "userLogin?password=%1&username=%2";

    url = url.arg(password).arg(name);

    QNetworkReply *reply = NULL;

    if( get(url, reply ) )
    {
        QString str = reply->readAll();
        Json json(str);

        int code = json.getInt("code");
        if( ERROR_CODE_REQUEST_SUCCESS == code )
        {
            QJsonObject obj = json.getJsonObject("data");
            QString token = json.getString("data.jwtToken", 0);

            //设置全局token和用户信息，在其他地方也可以使用
            HttpResponseManager::getInstance()->setToken(token);
            HttpResponseManager::getInstance()->setUserObject(obj);

            bret = true;
        }
        else
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), getErrorInfo(json, url));
        }
    }

    return bret;
}

bool UserManager::registerUser(const QString &name, const QString &password, const QString &desc, int role)
{
    bool bret = false;

    QString url = HttpResponseManager::getInstance()->getHttpPathBase();
    url += m_relativePath;
    url += "registerUser";

    QJsonDocument httpDocum;
    QJsonObject exampleObject;
    exampleObject.insert("password", password);
    exampleObject.insert("username", name);
    exampleObject.insert("roleId", role);
    exampleObject.insert("roleDesc", desc);

    httpDocum.setObject(exampleObject);

    QNetworkReply *reply = NULL;
    QByteArray data = httpDocum.toJson(QJsonDocument::Compact);

    if( post(url, data, reply ) )
    {
        QString str = reply->readAll();
        Json json(str);

        int code = json.getInt("code");
        if( ERROR_CODE_REQUEST_SUCCESS == code ) bret = true;
        else
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), getErrorInfo(json, url));
        }
    }

    return bret;
}
