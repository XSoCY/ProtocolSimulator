#include "communicationservicebase.h"

CommunicationServiceBase::CommunicationServiceBase(const ChannelAttributes &attrs, CommunicationService *service, QObject *parent)
    : m_running(true)
    , m_communicationService(service)
    , m_channel(nullptr)
    , m_attrs(attrs)
{
    m_channel = new CommunicationBase(attrs, parent);
    m_channel->setCreateHandle(this->bind());
    m_channel->start();
}

QString CommunicationServiceBase::getAttr(const QString &key)
{
    return m_channel->getAttr(key);
}

void CommunicationServiceBase::stop()
{
    m_channel->stop();
    m_running = false;
}

int CommunicationServiceBase::sendData(const QByteArray &data)
{
    return m_channel->sendData(data);
}

int CommunicationServiceBase::sendData(const QByteArray &data, QString ip)
{
    return m_channel->sendData(data,ip);
}

void CommunicationServiceBase::run()
{
    if( !m_channel ) return ;

    int itimeout = m_channel->getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    while( m_running )
    {
        if( m_channel->getMessageCount() > 0 )
        {
            MessageSharePointer data = m_channel->getMessage();
            if( data )
            {
                dataOpr(data);
            }
        }
        else QThread::msleep(itimeout);
    }
}
