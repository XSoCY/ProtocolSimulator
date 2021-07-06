#include "sysfaulttreemanager.h"
#include "httpresponsemanager.h"
#include "json.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QJsonArray>

SysFaultTreeManager::SysFaultTreeManager(QObject *parent)
    :httpResponseBase(parent)
{
    m_relativePath = "phm/fault/SysFaultTreeController/";
}

bool SysFaultTreeManager::getSysFaultBySysId(int sysId, SysFaultTreeItems &items)
{
    bool bret = false;

    QString url = HttpResponseManager::getInstance()->getHttpPathBase();
    url += m_relativePath;
    url += "getSysTreeBySysId?id=%1";

    url = url.arg(sysId);

    QNetworkReply *reply = NULL;
    if( get(url, reply ) )
    {
        QString str = reply->readAll();
        Json json(str);
        QJsonArray arr = json.getJsonArray("data");

        int code = json.getInt("code");
        if( ERROR_CODE_REQUEST_SUCCESS == code )
        {
            bret = true;

            for(int i=0; i<arr.count(); ++i)
            {
                QJsonValue objTmp = arr.at(i);
                int id = json.getInt("id", 0, objTmp.toObject());
                items[id] = objTmp.toObject();
            }
        }
    }
    else
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "请求失败：" + url);
    }
    return bret;
}

bool SysFaultTreeManager::getSysTreeById(int id, QJsonObject &sysTree)
{
    bool bret = false;

    QString url = HttpResponseManager::getInstance()->getHttpPathBase();
    url += m_relativePath;
    url += "getSysTreeById?id=%1";

    url = url.arg(id);

    QNetworkReply *reply = NULL;
    if( get(url, reply ) )
    {
        QString str = reply->readAll();

        Json json(str);
        int code = json.getInt("code");
        if( ERROR_CODE_REQUEST_SUCCESS == code )
        {
            bret = true;
            sysTree = json.getJsonObject("data");
        }
        else
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), getErrorInfo(json, url));
        }
    }
    else
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "请求失败：" + url);
    }
    return bret;
}

bool SysFaultTreeManager::updateSysFaultTree(const QByteArray &value)
{
    bool bret = false;

    QString url = HttpResponseManager::getInstance()->getHttpPathBase();
    url += m_relativePath;
    url += "putSysFaultTree";

    QNetworkReply *reply = NULL;
    if( put(url, value, reply ) )
    {
        QString str = reply->readAll();

        qDebug() << "str: " << str;

        Json json(str);
        int code = json.getInt("code");
        if( ERROR_CODE_UPDATE_SUCCESS == code ) bret = true;
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), getErrorInfo(json, url));
        }
    }

    return bret;
}

bool SysFaultTreeManager::updateSysFaultTree(const QJsonDocument &value)
{
    QByteArray data = value.toJson(QJsonDocument::Compact);
    return updateSysFaultTree(data);
}
