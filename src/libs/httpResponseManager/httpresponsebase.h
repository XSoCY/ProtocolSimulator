#ifndef HTTPRESPONSEBASE_H
#define HTTPRESPONSEBASE_H

#include "httpresponsemanager_global.h"
#include "log.h"
#include "errorcode.h"
#include "Json.h"

#include <QObject>
#include <QNetworkReply>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QTimer>
#include <QEventLoop>

using namespace HTTP_ERROR_CODE;

#define FIELD_CODE      "code"
#define FIELD_MESSAGE   "message"
#define FIELD_DATA      "data"

class HTTPRESPONSEMANAGERSHARED_EXPORT httpResponseBase : public QObject
{
    Q_OBJECT
public:
    httpResponseBase(QObject *parent=nullptr);

    bool get(const QString &url, QNetworkReply *&reply);
    bool put(const QString &url, const QByteArray &data, QNetworkReply *&reply);
    bool post(const QString &url, const QByteArray &data, QNetworkReply *&reply);
    bool deleteSoure(const QString &url, const QByteArray &data, QNetworkReply *&reply);

    void setTimeout(int timeout);
    void setRelativePath(const QString &path);

protected:
    bool Asyn(QNetworkAccessManager* manager, int timeout);

    bool execRequest(QNetworkAccessManager* manager, QNetworkReply *&reply);
    QString getErrorInfo(const Json &json, const QString &url);
protected:
    QMutex                                  m_threadMutex;   //消息互斥
    QWaitCondition                          m_waitObj;
    QEventLoop                              m_eventLoop;

    int                                     m_timeOut;
    QNetworkReply                           *m_reply;

    QString                                 m_relativePath;
};

#endif // HTTPRESPONSEBASE_H
