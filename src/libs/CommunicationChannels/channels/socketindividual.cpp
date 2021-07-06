#include "socketindividual.h"
#include "log.h"

SocketIndividual::SocketIndividual(QTcpSocket *socket,const ChannelAttributes &attrs, QObject *parent)
    : ChannelBase(attrs, parent),
      m_running(true),
      m_tcpSocket(socket)
{
}

void SocketIndividual::receiveData()
{
    m_tcpSocket->waitForReadyRead(10);
    QByteArray bytes = m_tcpSocket->readAll();

    qDebug() << "socket peerPort: " << getPeerPort();
    qDebug() << bytes.toHex();

    if( !bytes.isEmpty() ) addMessage(bytes);
}

void SocketIndividual::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << error;
    setConnectError(error);
}

void SocketIndividual::closeChannel()
{

}

int SocketIndividual::sendData(const QByteArray &data)
{
    qDebug() << "socket send data: " << data.toHex();
    return sendData(data.data(), data.length());
}

void SocketIndividual::run()
{
    int itimeout = getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    while( m_running )
    {
        if( getMessageCount() > 0 )
        {
            MessageSharePointer data = getMessage();
            if( data ) dataOpr(data, getPeerPort());
        }
        else QThread::msleep(itimeout);
    }
}

int SocketIndividual::sendData(const char *data, int len)
{
    if( !m_tcpSocket ) return 0;

    if ( !m_tcpSocket->isValid() )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "InterfaceDisconnected!");
        return 0;
    }
    else
    {
        int sendLen = m_tcpSocket->write(data, len);
        if( sendLen < 0 )
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QStringLiteral("send error: %1")
                                         .arg(m_tcpSocket->errorString()));
        }
        return sendLen;
    }
}

QTcpSocket *SocketIndividual::getTcpSocket()
{
    return m_tcpSocket;
}

QString SocketIndividual::getPeerPort()
{
    return QString::number(m_tcpSocket->peerPort());
}

void SocketIndividual::waitForReadyRead()
{
    int itimeout = 0;

    itimeout = getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    if( m_tcpSocket ) m_tcpSocket->waitForReadyRead(itimeout);
}

void SocketIndividual::stop()
{
    m_running = false;
    this->quit();
}
