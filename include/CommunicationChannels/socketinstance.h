#ifndef SOCKETINSTANCE_H
#define SOCKETINSTANCE_H
#include "socketindividual.h"

#define PEERADDRESS "192.168.105.97"

class socketInstance : public SocketIndividual
{
public:
    socketInstance(QTcpSocket *socket, const ChannelAttributes &attrs, QObject *parent = nullptr);

    void dataOpr(const MessageSharePointer data, QString dataIP);
};

#endif // SOCKETINSTANCE_H
