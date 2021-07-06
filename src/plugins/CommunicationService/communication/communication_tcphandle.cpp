#include "communication_tcphandle.h"
#include <qDebug>
communication_tcphandle::communication_tcphandle(QTcpSocket *socket,const ChannelAttributes &attrs, QObject *parent)
    : SocketIndividual(socket, attrs, parent)
{

}

void communication_tcphandle::dataOpr(const MessageSharePointer data, QString dataPort)
{
    qDebug() << "here is communication_tcphandle";
}
