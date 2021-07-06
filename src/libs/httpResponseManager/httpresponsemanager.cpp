#include "httpresponsemanager.h"

HttpResponseManager *HttpResponseManager::m_instance = NULL;

void HttpResponseManager::setHttpPathBase(const QString &url)
{
    m_httpPathBase = url;
}

QString HttpResponseManager::getHttpPathBase()
{
    return m_httpPathBase;
}

void HttpResponseManager::setToken(const QString &token)
{
    m_token = token;
}

QString HttpResponseManager::getToken()
{
    return m_token;
}

void HttpResponseManager::setUserObject(const QJsonObject &userInfo)
{
    m_userObject = userInfo;
}

QJsonObject HttpResponseManager::getUserObject()
{
    return m_userObject;
}

HttpResponseManager::HttpResponseManager()
{
    m_httpPathBase = "http://192.168.31.2:8082/";
    m_token = "";
}
