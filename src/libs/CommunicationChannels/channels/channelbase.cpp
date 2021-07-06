#include "channelbase.h"
#include "log.h"

#include <QMap>
#include <QThread>

ChannelBase::ChannelBase(const ChannelAttributes &attrs, QObject *parent)
{
    setChannelAttr(attrs);
}

ChannelBase::~ChannelBase()
{

}

void ChannelBase::setChannelAttr(const ChannelAttributes &attrs)
{
    m_mapAttrs = attrs;
}

QString ChannelBase::getAttr(const QString &key)
{
    if( m_mapAttrs.contains(key) )
    {
        return m_mapAttrs[key];
    }

    return QString("");
}

QMap<QString, QString> ChannelBase::getAttr()
{
    return m_mapAttrs;
}

void ChannelBase::setConnectState(QAbstractSocket::SocketState state)
{
    m_connectState = state;
}

QAbstractSocket::SocketState ChannelBase::getConnectState()
{
    return m_connectState;
}

void ChannelBase::setConnectError(QAbstractSocket::SocketError error)
{
    m_connectError = error;
}

QAbstractSocket::SocketError ChannelBase::getConnectError()
{
    return m_connectError;
}

bool ChannelBase::addMessage(const QByteArray &msg)
{
    QMutexLocker locker(&m_messageMutex);

    MessageSharePointer tmp(new QByteArray(msg));
    m_messageQueue.append(tmp);

    addReceiveCount(msg.length());
    return true;
}

bool ChannelBase::delMessage(int count, int index)
{
    QMutexLocker locker(&m_messageMutex);

    //全部删除
    if( 0 == count && 0 == index ) m_messageQueue.clear();

    QList<QSharedPointer<QByteArray>>::iterator itor = m_messageQueue.begin()+index;
    int iDelCount = 0;
    for( itor; itor<m_messageQueue.end(); )
    {
        itor = m_messageQueue.erase(itor);

        ++iDelCount;
        if( iDelCount >= count ) break;
    }

    return true;
}

MessageSharePointer ChannelBase::getMessage()
{
    QMutexLocker locker(&m_messageMutex);

    if( m_messageQueue.size() <= 0 ) return NULL;

    MessageSharePointer tmp = m_messageQueue[0];
    m_messageQueue.removeAt(0);

    return tmp;
}

int ChannelBase::getMessageCount()
{
    QMutexLocker locker(&m_messageMutex);
    return m_messageQueue.size();
}

ChannelType ChannelBase::getChannelType()
{
    return (ChannelType)(getAttr(CHANNEL_TYPE).toInt());
}

void ChannelBase::addSendCount(int len)
{
    m_sendCount += len;
}

void ChannelBase::addReceiveCount(int len)
{
    m_receiveCount += len;
}

uint ChannelBase::getSendCount()
{
    return m_sendCount;
}

uint ChannelBase::getReveiveCount()
{
    return m_receiveCount;
}

