#ifndef COMMUNICATION_TCPHANDLE_H
#define COMMUNICATION_TCPHANDLE_H

#include "socketindividual.h"
#include "tcpserverchannel.h"

class communication_tcphandle : public SocketIndividual
{
public:
    communication_tcphandle(QTcpSocket *socket, const ChannelAttributes &attrs, QObject *parent = nullptr);

    /**
     * @brief DataOpr 处理此通道收到的数据
     * @param data 收到客户端数据
     * @return 无
     */
    void dataOpr(const MessageSharePointer data, QString dataPort);
};

#endif // COMMUNICATION_TCPHANDLE_H
