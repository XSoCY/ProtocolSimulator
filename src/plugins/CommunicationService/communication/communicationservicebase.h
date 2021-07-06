#ifndef COMMUNICATIONSERVICEBASE_H
#define COMMUNICATIONSERVICEBASE_H

#include <QThread>
#include "communicationbase.h"
#include "communication_tcphandle.h"

class CommunicationService;
using namespace std;
using namespace std::placeholders;
class CommunicationServiceBase : public QThread
{
    Q_OBJECT
public:
    CommunicationServiceBase(const ChannelAttributes &attrs
                             , CommunicationService *service
                             , QObject *parent=nullptr);

    /**
     * @brief getAttr  获取通道参数
     * @param key     参数的key值
     * @return 无
     */
    virtual QString getAttr(const QString &key);

    void stop();

    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    virtual int sendData(const QByteArray &data);

    int sendData(const QByteArray &data, QString ip);

    _createCallback bind()
    {
        return  std::bind(&CommunicationServiceBase::func, this, _1,_2);
    }

    SocketIndividual* func(QTcpSocket *socket, const ChannelAttributes &attrs)
    {
        return new communication_tcphandle(socket, attrs);
    }

protected:
    /**
     * @brief DataOpr 处理此通道收到的数据
     * @param data 收到客户端数据
     * @return 无
     */
    virtual void dataOpr(const MessageSharePointer data) = 0;

protected:
    void run();

protected:
    CommunicationService    *m_communicationService;

private:

    CommunicationBase       *m_channel;

    bool                    m_running;
    ChannelAttributes       m_attrs;

};

#endif // COMMUNICATIONSERVICEBASE_H
