#include "udpchannel.h"
#include "log.h"

UdpChannel::UdpChannel(const ChannelAttributes &attrs, QObject *parent)
    :ChannelBase(attrs, parent)
    , m_udpReceveSocket(nullptr)
    , m_udpSendSocket(nullptr)
{
    if( init() ) setConnectState(QAbstractSocket::SocketState::ConnectedState);
}

UdpChannel::~UdpChannel()
{

}

bool UdpChannel::init()
{
    if (!m_udpReceveSocket) {
        m_udpReceveSocket = new QUdpSocket;

        //增大缓存
        m_udpReceveSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 128 * 1024 * 1024);
        m_udpReceveSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 128 * 1024 * 1024);
    }

    if( !connect(m_udpReceveSocket, SIGNAL(readyRead()), this, SLOT(receiveData())) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "connect readyRead fail!");
    }

    if ( !m_udpReceveSocket->bind(QHostAddress::AnyIPv4, getAttr(CHANNEL_LOCAL_PORT).toInt(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT()
                                     , QStringLiteral("%1Bind失败! 原因:%3!")
                                     .arg(getAttr(CHANNEL_ID))
                                     .arg(m_udpReceveSocket->errorString()));
        return false;
    }
    else
    {
        connect(m_udpReceveSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    }

    if( CHANNEL_TYPE_UDP_MULTICAST == getChannelType() )
    {   //如果是组播，则需要加入组播地址
        m_udpReceveSocket->setMulticastInterface(getNetwork());

        if( !m_udpReceveSocket->joinMulticastGroup(QHostAddress(getAttr(CHANNEL_REMOTE_IP)), getNetwork()) )
        {   //设置组播
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT()
                                         , QStringLiteral("add multicast fail! error: %1; channelid: %2; localip: %3; lacolport: %4; remoteip: %5; remoteport: %6")
                                         .arg(m_udpReceveSocket->errorString())
                                         .arg(getAttr(CHANNEL_ID))
                                         .arg(getAttr(CHANNEL_LOCAL_IP))
                                         .arg(getAttr(CHANNEL_LOCAL_PORT))
                                         .arg(getAttr(CHANNEL_REMOTE_IP))
                                         .arg(getAttr(CHANNEL_REMOTE_PORT)));
            return false;
        }
    }

    Log::getInstance()->writeLog(LOG_LEVEL_PROMPT, LOG_DATA_FORMAT()
                                 , QStringLiteral("Create channel success! info: %1; channelid: %2; localip: %3; lacolport: %4; remoteip: %5; remoteport: %6")
                                 .arg(m_udpReceveSocket->errorString())
                                 .arg(getAttr(CHANNEL_ID))
                                 .arg(getAttr(CHANNEL_LOCAL_IP))
                                 .arg(getAttr(CHANNEL_LOCAL_PORT))
                                 .arg(getAttr(CHANNEL_REMOTE_IP))
                                 .arg(getAttr(CHANNEL_REMOTE_PORT)));
    return true;
}

void UdpChannel::closeChannel()
{

}

int UdpChannel::sendData(const QByteArray &data)
{
    return sendData(data.data(), data.length());
}

int UdpChannel::sendData(const char *data, int len)
{
    if( !m_udpSendSocket ) m_udpSendSocket = new QUdpSocket;

    int sendLen = 0;
    if( CHANNEL_TYPE_UDP_BROADCAST == getAttr(CHANNEL_TYPE).toInt() )
    {   //广播时地址不一样
        sendLen = m_udpSendSocket->writeDatagram(data, len, QHostAddress::Broadcast, getAttr(CHANNEL_REMOTE_PORT).toInt());
    } //组播和点对点
    else sendLen = m_udpSendSocket->writeDatagram(data, len, QHostAddress(getAttr(CHANNEL_REMOTE_IP)), getAttr(CHANNEL_REMOTE_PORT).toInt());

    if( sendLen < 0 )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QStringLiteral("send error ip: %1; port: %2; error: %3")
                                     .arg(getAttr(CHANNEL_REMOTE_IP))
                                     .arg(getAttr(CHANNEL_REMOTE_PORT))
                                     .arg(m_udpSendSocket->errorString()));
    }

    return sendLen;
}

void UdpChannel::waitForReadyRead()
{
    int itimeout = 0;

    itimeout = getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    if( m_udpReceveSocket ) m_udpReceveSocket->waitForReadyRead(itimeout);
}


void UdpChannel::receiveData()
{
    while ( m_udpReceveSocket->hasPendingDatagrams() )
    {
        QHostAddress rHost;
        quint16 rPort;
        QByteArray bytes;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 8, 0))
        QNetworkDatagram datagram = m_udpReceveSocket->receiveDatagram();
        rHost = datagram.senderAddress();
        rPort = datagram.senderPort();
        bytes = datagram.data();
#else
        bytes.resize(m_udpReceveSocket->pendingDatagramSize()); //返回大小
        m_udpReceveSocket->readDatagram(bytes.data(), bytes.size(), &rHost, &rPort);
#endif

        qDebug() << bytes.toHex();
        if( !bytes.isEmpty() ) addMessage(bytes);
    }
}

void UdpChannel::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << error;
    setConnectError(error);

    //后续根据错误设置网络状态
}

int UdpChannel::sendDataLot(const QByteArray &data)
{
    return sendData(data);
}

QNetworkInterface UdpChannel::getNetwork()
{
    const QList<QNetworkInterface>& networkInterfaces = QNetworkInterface::allInterfaces();
    for(int i=0; i<networkInterfaces.size(); ++i)
    {
        foreach(QNetworkAddressEntry addr, networkInterfaces[i].addressEntries())
        {
            if (addr.ip().toString().trimmed().toLower() == getAttr(CHANNEL_LOCAL_IP))
            {
                return networkInterfaces[i];
            }
        }
    }

    return QNetworkInterface();
}

