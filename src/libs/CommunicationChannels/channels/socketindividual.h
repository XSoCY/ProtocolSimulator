#ifndef SOCKETINDIVIDUAL_H
#define SOCKETINDIVIDUAL_H

#include "channelbase.h"
#include <QTcpSocket>

#define Client1 "52198"   //此处定义要分别处理的客户端端口
#define Client2 "52193"
#define Client3 "52195"

class COMMUNICATIONCHANNELSSHARED_EXPORT SocketIndividual : public ChannelBase, public QThread, public QObject
{
    Q_OBJECT
public:
    SocketIndividual(QTcpSocket *socket, const ChannelAttributes &attrs, QObject *parent = nullptr);

    /**
     * @brief closeChannel 关闭通讯通道
     * @return 无
     */
    void closeChannel();
    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @param len 数据长度
     * @return 发送数据的长度
     */
    int sendData(const char *data, int len);
    /**
     * @brief getTcpSocket 获取对应的套接字
     * @return 该对象所代表的套接字
     */
    QTcpSocket* getTcpSocket();
    /**
     * @brief getPeerPort 获取对应的连接端口
     * @return 连接端口
     */
    QString getPeerPort();
    /**
     * @brief waitForReadyRead 等待ReadyRead信号
     * @return 无
     */
    void waitForReadyRead();
    /**
     * @brief stop 暂停线程进行处理
     */
    void stop();

public slots:
    /**
     * @brief receiveData  接收数据槽函数
     * @return 无
     */
    void receiveData();
    /**
     * @brief onSocketError  网络错误槽函数
     * @return 无
     */
    void onSocketError(QAbstractSocket::SocketError error);
    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    int sendData(const QByteArray &data);

protected:
    void run();
    /**
     * @brief DataOpr 处理此通道收到的数据
     * @param data 收到客户端数据
     * @return 无
     */
    virtual void dataOpr(const MessageSharePointer data, QString dataPort) = 0;

private:
    bool                    m_running;
    QTcpSocket              *m_tcpSocket;
};

#endif // SOCKETINDIVIDUAL_H
