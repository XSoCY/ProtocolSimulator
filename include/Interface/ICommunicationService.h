#ifndef ICOMMUNICATION_SERVICE_INTERFACE_H
#define ICOMMUNICATION_SERVICE_INTERFACE_H

#include <QByteArray>
#include <QString>

class ICommunicationServiceInterface
{
public:
    virtual ~ICommunicationServiceInterface() {}

    virtual int sendMessage(const QString &channelId, const QByteArray &data) = 0;

    virtual int sendMessage(const QString &channelId, const QByteArray &data, QString sendIP){ return 0; }
};

#endif  // ITEST_SERVICE_INTERFACE_H
