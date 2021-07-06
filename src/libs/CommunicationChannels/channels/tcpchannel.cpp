#include "tcpchannel.h"
#include "log.h"

TcpChannel::TcpChannel(const ChannelAttributes &attrs, QObject *parent)
    : ChannelBase(attrs, parent)
    , m_tcpSocket(nullptr)
{
    if( init() ) setConnectState(QAbstractSocket::SocketState::ConnectedState);
}

TcpChannel::~TcpChannel()
{
    m_timer->stop();
    delete m_timer;
    m_timer = nullptr;

    if(m_tcpSocket)
    {
        delete m_tcpSocket;
        m_tcpSocket = nullptr;
    }
}

bool TcpChannel::init()
{
    if (!m_tcpSocket) {
        m_tcpSocket = new QTcpSocket;
        //增大缓存
        m_tcpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 128 * 1024 * 1024);
        m_tcpSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 128 * 1024 * 1024);
    }

    if ( !m_tcpSocket->bind(QHostAddress::AnyIPv4, getAttr(CHANNEL_LOCAL_PORT).toInt(), QTcpSocket::ShareAddress | QTcpSocket::ReuseAddressHint) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT()
                                     , QStringLiteral("%1Bind失败! 原因:%3!")
                                     .arg(getAttr(CHANNEL_ID))
                                     .arg(m_tcpSocket->errorString()));
        return false;
    }
    else
    {
        connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    }

    m_tcpSocket->connectToHost(getAttr(CHANNEL_REMOTE_IP), getAttr(CHANNEL_REMOTE_PORT).toInt());

    if(!m_tcpSocket->waitForConnected(1000))
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "Connect fail!");
        return false;
    }

    if( !connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData())) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "connect readyRead fail!");
    }
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));

    Log::getInstance()->writeLog(LOG_LEVEL_PROMPT, LOG_DATA_FORMAT()
                                 , QStringLiteral("Create channel success! info: %1; channelid: %2; localip: %3; lacolport: %4; remoteip: %5; remoteport: %6")
                                 .arg(m_tcpSocket->errorString())
                                 .arg(getAttr(CHANNEL_ID))
                                 .arg(getAttr(CHANNEL_LOCAL_IP))
                                 .arg(getAttr(CHANNEL_LOCAL_PORT))
                                 .arg(getAttr(CHANNEL_REMOTE_IP))
                                 .arg(getAttr(CHANNEL_REMOTE_PORT)));

    m_timer = new QTimer(this); //定时器检查是否需要重新连接
    connect(m_timer, SIGNAL(timeout()),this,SLOT(onTcpClientReConnect()));
    m_timer->setInterval(3000);
    m_timer->start();

    return true;
}

void TcpChannel::closeChannel()
{

}

int TcpChannel::sendData(const QByteArray &data)
{
    return sendData(data.data(), data.length());
}

int TcpChannel::sendData(const char *data, int len)
{
    if( !m_tcpSocket ) m_tcpSocket = new QTcpSocket;

    //若为未连接状态，重新建立连接
    if ( getConnectState() != QTcpSocket::ConnectedState )
    {
        m_tcpSocket->connectToHost(getAttr(CHANNEL_REMOTE_IP), getAttr(CHANNEL_REMOTE_PORT).toInt());
        setConnectState(m_tcpSocket->state());
    }

    int sendLen = m_tcpSocket->write(data, len);

    if( sendLen < 0 )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QStringLiteral("send error ip: %1; port: %2; error: %3")
                                     .arg(getAttr(CHANNEL_REMOTE_IP))
                                     .arg(getAttr(CHANNEL_REMOTE_PORT))
                                     .arg(m_tcpSocket->errorString()));
    }

    return sendLen;
}

void TcpChannel::waitForReadyRead()
{
    int itimeout = 0;

    itimeout = getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    if( m_tcpSocket ) m_tcpSocket->waitForReadyRead(itimeout);
}

void TcpChannel::receiveData()
{
    m_tcpSocket->waitForReadyRead(10);
    QByteArray bytes = m_tcpSocket->readAll();

    if( !bytes.isEmpty() ) addMessage(bytes);
}

int TcpChannel::sendDataLot(const QByteArray &data)
{
    return sendData(data);
}

void TcpChannel::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << error;
    setConnectError(error);

    //后续根据错误设置网络状态
}

void TcpChannel::onDisconnected()
{
    setConnectState(m_tcpSocket->state());
    m_timer->start();
}

void TcpChannel::onTcpClientReConnect()
{
    if (getConnectState() == QTcpSocket::ConnectedState)
    {
        m_timer->stop();
        return;
    }
    else
    {
        m_tcpSocket->connectToHost(getAttr(CHANNEL_REMOTE_IP), getAttr(CHANNEL_REMOTE_PORT).toInt());
        setConnectState(m_tcpSocket->state());

        if (getConnectState() == QTcpSocket::ConnectedState)
            m_timer->stop();
    }
}
