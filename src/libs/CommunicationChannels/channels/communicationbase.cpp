#include "communicationbase.h"
#include "log.h"

CommunicationBase::CommunicationBase(const ChannelAttributes &attrs, QObject *parent)
    : m_attrs(attrs)
    , m_running(true)
    , m_timingCall(0)
    , m_channel(nullptr)
{

}

void CommunicationBase::stop()
{
    this->quit();
}

void CommunicationBase::setCreateHandle(_createCallback f)
{
    m_fun = f;
}

_createCallback CommunicationBase::getHandle()
{
    return m_fun;
}

int CommunicationBase::sendData(const QByteArray &data)
{
    emit signalSend(data);

    //目前是返回假的长度，后续完善
    return data.length();
}

int CommunicationBase::sendData(const QByteArray &data, QString ip)
{
    emit tcpSignalSend(data, ip);

    return data.length();
}

QString CommunicationBase::getAttr(const QString &key)
{
    if(m_attrs.contains(key)) return m_attrs[key];

    return QString("");
}

ChannelAttributes CommunicationBase::getAttr()
{
    if( m_channel ) return m_channel->getAttr();
}

QAbstractSocket::SocketState CommunicationBase::getConnectState()
{
    if( m_channel ) return m_channel->getConnectState();
    return QAbstractSocket::UnconnectedState;
}

QAbstractSocket::SocketError CommunicationBase::getConnectError()
{
    if( m_channel ) return m_channel->getConnectError();
    return QAbstractSocket::NetworkError;
}

bool CommunicationBase::delMessage(int count, int index)
{
    if( m_channel ) return m_channel->delMessage(count, index);

    return false;
}

MessageSharePointer CommunicationBase::getMessage()
{
    if( m_channel ) return m_channel->getMessage();

    return nullptr;
}

int CommunicationBase::getMessageCount()
{
    if( m_channel ) return m_channel->getMessageCount();

    return 0;
}

void CommunicationBase::closeChannel()
{
    if( m_channel ) m_channel->closeChannel();
}

uint CommunicationBase::getSendCount()
{
    if( m_channel ) return m_channel->getSendCount();

    return 0;
}

uint CommunicationBase::getReveiveCount()
{
    if( m_channel ) return m_channel->getReveiveCount();

    return 0;
}

void CommunicationBase::run()
{
    if( !m_attrs.contains(CHANNEL_TYPE) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "Unknow channel type!");
        return;
    }

    ChannelType channelType = (ChannelType)(m_attrs[CHANNEL_TYPE].toInt());

    if( CHANNEL_TYPE_UDP_P2P == channelType
        || CHANNEL_TYPE_UDP_BROADCAST == channelType
        || CHANNEL_TYPE_UDP_MULTICAST == channelType )
    {
        m_channel = new UdpChannel(m_attrs);
        connect(this, SIGNAL(signalSend(QByteArray)), m_channel, SLOT(sendDataLot(QByteArray)));
    }
    else if(CHANNEL_TYPE_COMM == channelType)
    {
        m_channel = new CommChannel(m_attrs);
        connect(this, SIGNAL(signalSend(QByteArray)), m_channel, SLOT(sendDataLot(QByteArray)));
    }
    else if(CHANNEL_TYPE_TCP_CLIENT == channelType)
    {
        m_channel = new TcpChannel(m_attrs);
        connect(this, SIGNAL(signalSend(QByteArray)), m_channel, SLOT(sendDataLot(QByteArray)));
    }
    else if(CHANNEL_TYPE_TCP_SERVER == channelType)
    {
        m_channel = new TcpServerChannel(m_attrs);
        m_channel->setHandlePtr(getHandle());
        connect(this, SIGNAL(tcpSignalSend(QByteArray, QString)), m_channel, SLOT(sendDataLot(QByteArray, QString)));
    }


    this->exec();

    delete m_channel;
    m_channel = nullptr;
}
