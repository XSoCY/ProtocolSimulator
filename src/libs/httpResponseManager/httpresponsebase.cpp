#include "httpresponsebase.h"
#include "httpresponsemanager.h"
#include "log.h"

#include <QEventLoop>
#include <QTimer>
#include <QThread>

httpResponseBase::httpResponseBase(QObject *parent)
    : QObject(parent)
    , m_timeOut(10000)
{

}

bool httpResponseBase::get(const QString &url, QNetworkReply *&reply)
{
    QMutexLocker locker(&m_threadMutex);
    bool bret = false;

    //如果未登录且不是登录请求则返回false
    if( HttpResponseManager::getInstance()->getToken().isEmpty() && !url.contains("userLogin", Qt::CaseSensitive) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "未登录");
        return false;
    }

    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    request.setUrl(QUrl(url));
    request.setRawHeader("token", HttpResponseManager::getInstance()->getToken().toLocal8Bit());

    reply = manager->get(request);

    return execRequest(manager, reply);
}

bool httpResponseBase::put(const QString &url, const QByteArray &data, QNetworkReply *&reply)
{
    QMutexLocker locker(&m_threadMutex);
    bool bret = false;

    //如果未登录且不是登录请求则返回false
    if( HttpResponseManager::getInstance()->getToken().isEmpty() && !url.contains("userLogin", Qt::CaseSensitive) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "未登录");
        return false;
    }

    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("token", HttpResponseManager::getInstance()->getToken().toLocal8Bit());

    reply = manager->put(request, data);

    return execRequest(manager, reply);
}

bool httpResponseBase::post(const QString &url, const QByteArray &data, QNetworkReply *&reply)
{
    QMutexLocker locker(&m_threadMutex);
    bool bret = false;

    //如果未登录且不是登录请求则返回false
    if( HttpResponseManager::getInstance()->getToken().isEmpty() && !url.contains("userLogin", Qt::CaseSensitive) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "未登录");
        return false;
    }

    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("token", HttpResponseManager::getInstance()->getToken().toLocal8Bit());

    reply = manager->post(request, data);

    return execRequest(manager, reply);
}

bool httpResponseBase::deleteSoure(const QString &url, const QByteArray &data, QNetworkReply *&reply)
{
    QMutexLocker locker(&m_threadMutex);
    bool bret = false;

    //如果未登录且不是登录请求则返回false
    if( HttpResponseManager::getInstance()->getToken().isEmpty() && !url.contains("userLogin", Qt::CaseSensitive) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "未登录");
        return false;
    }

    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("token", HttpResponseManager::getInstance()->getToken().toLocal8Bit());

    reply = manager->deleteResource(request);

    return execRequest(manager, reply);
}

void httpResponseBase::setTimeout(int timeout)
{
    m_timeOut = timeout;
}

void httpResponseBase::setRelativePath(const QString &path)
{
    m_relativePath = path;
}

bool httpResponseBase::Asyn(QNetworkAccessManager *manager, int timeout)
{
    if( !manager ) return false;

    bool bret = false;

    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QTimer timer;
    timer.setInterval(timeout);
    timer.setSingleShot(true);

    QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timer.start();

    eventLoop.exec();

    if( timer.isActive() )
    {
        timer.stop();
        bret = true;
    }
    else bret = false;

    return bret;
}

bool httpResponseBase::execRequest(QNetworkAccessManager *manager, QNetworkReply *&reply)
{
    bool bret = false;

    if( Asyn(manager, m_timeOut) )
    {
        QVariant variant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if( 200 == variant.toInt() ) bret = true;
        else
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), reply->readAll());
            bret = false;
        }
    }
    else
    {
        QString error = "未知原因";
        if( reply ) error = reply->readAll();

        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "get Request timeout: "+error);
        bret = false;
    }

    return bret;
}

QString httpResponseBase::getErrorInfo(const Json &json, const QString &url)
{
    return "url: " + url + "Error code: " + QString::number(json.getInt(FIELD_CODE)) + " message: "+json.getString(FIELD_MESSAGE);
}
