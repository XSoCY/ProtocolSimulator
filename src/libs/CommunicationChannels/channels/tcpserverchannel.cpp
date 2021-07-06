#include "tcpserverchannel.h"
#include "log.h"
#include "socketindividual.h"
TcpServerChannel::TcpServerChannel(const ChannelAttributes &attrs, QObject *parent)
    : ChannelBase(attrs, parent)
    , m_tcpServer(nullptr)
    , m_socket(nullptr)
    , m_mapAttrs(attrs)
{
    init();
}

TcpServerChannel::~TcpServerChannel()
{
    if(m_tcpServer)
    {
        delete m_tcpServer;
        m_tcpServer = nullptr;
    }
}

bool TcpServerChannel::init()
{
    if (!m_tcpServer) m_tcpServer = new QTcpServer;

    //建立端口的监听
    if (!m_tcpServer->listen(QHostAddress::AnyIPv4, getAttr(CHANNEL_LOCAL_PORT).toInt())){
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT()
                                     , QStringLiteral("%1Listen失败! 原因:%3!")
                                     .arg(getAttr(CHANNEL_ID))
                                     .arg(m_tcpServer->errorString()));
        return false;
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));

    return true;
}

void TcpServerChannel::setHandlePtr(_createCallback f)
{
    p_fun = f;
}

void TcpServerChannel::closeChannel()
{

}

int TcpServerChannel::sendData(const QByteArray &data)
{
    return sendData(data.data(), data.length());
}

int TcpServerChannel::sendData(const char *data, int len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 1;
}

void TcpServerChannel::waitForReadyRead()
{
    for (int i = 0; i < m_socketList.length(); i++)
    {
        if(m_socketList.at(i)->getTcpSocket())
        {
            m_socketList.at(i)->waitForReadyRead();
        }
    }
}

bool TcpServerChannel::delMessage(int count, int index)
{
    for (int i = 0; i < m_socketList.length(); i++)
    {
        if(m_socketList.at(i))
        {
            m_socketList.at(i)->delMessage(count, index);
        }
    }
    return true;
}

int TcpServerChannel::sendDataLot(const QByteArray &data, QString port)
{
    qDebug() << "tcp server send data: " << data.toHex();
    for (int i = 0; i < m_socketList.length(); i++)
    {
        if(m_socketList.at(i)->getPeerPort() == port)
        {
            return m_socketList.at(i)->sendData(data);
        }
    }
    return 0;
}

void TcpServerChannel::ServerNewConnection()
{
    QTcpSocket *socket = m_tcpServer->nextPendingConnection();

    if ( !socket ){
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "Connect fail!");
        return;
    }

    m_socket = p_fun(socket, m_mapAttrs);
    m_socket->start();
    m_socketList.append(m_socket);

    if( !connect(socket, SIGNAL(readyRead()), m_socket, SLOT(receiveData())) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "Connect readyRead fail!");
    }
    else
    {
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), m_socket, SLOT(onSocketError(QAbstractSocket::SocketError)));
    }

    connect(socket, SIGNAL(disconnected()), this, SLOT(ServerDisConnection()));
    Log::getInstance()->writeLog(LOG_LEVEL_PROMPT, LOG_DATA_FORMAT()
                                 , QStringLiteral("Create channel success! info: %1;")
                                 .arg(socket->errorString()));
}

void TcpServerChannel::ServerDisConnection()
{
    Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "InterfaceDisconnected!");

    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    for (int i = 0; i < m_socketList.length(); i++)
    {
        if (socket == m_socketList.at(i)->getTcpSocket())
        {
            SocketIndividual *removeSocket = m_socketList.at(i);
            removeSocket->stop();

            m_socketList.removeAt(i);

//            delete removeSocket;
//            removeSocket = nullptr;
        }
    }
}
