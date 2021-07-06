/*
 * TCP通道:此类主要创建TCP服务端通讯通道
 * 创建者：zengl
 * 创建日期：2021-03-18
 */
#ifndef TCPSERVERCHANNEL_H
#define TCPSERVERCHANNEL_H

#include "channelbase.h"
#include <QThread>

class COMMUNICATIONCHANNELSSHARED_EXPORT TcpServerChannel : public ChannelBase
{
    Q_OBJECT
public:
    TcpServerChannel(const ChannelAttributes &attrs, QObject *parent = nullptr);
    ~TcpServerChannel();

    /**
     * @brief init  根据通道参数，初始化通道
     * @return 无
     */
    bool init();

    _createCallback p_fun;

    void setHandlePtr(_createCallback f);

public:
    /**
     * @brief closeChannel 关闭通讯通道
     * @return 无
     */
    void closeChannel();
    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    int sendData(const QByteArray &data);
    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @param len 数据长度
     * @return 发送数据的长度
     */
    int sendData(const char *data, int len);
    /**
     * @brief waitForReadyRead 等待ReadyRead信号
     * @return 无
     */
    void waitForReadyRead();

    /**
     * @brief delMessage 当缓冲区数据量比较大时，删除缓冲区数据（从头往后删，先入先删）
     * @param count 删除数量，当数量为0时，删除index后的所有数据
     * @param index 从某个点开始删除，默认从头开始
     * @return 无
     */
    bool delMessage(int count=0, int index=0);

public slots:
    /**
     * @brief sendDataLot 发送数据槽函数
     * @param data 要发送的数据
     * @param ipPort 要发送的端口号
     * @return  发送数据的长度
     */
    int sendDataLot(const QByteArray &data, QString port);

    /**
     * @brief ServerNewConnection 服务端接收到连接槽函数
     * @return 无
     */
    void ServerNewConnection();

    /**
     * @brief ServerDisConnection 连接中断
     * @return 无
     */
    void ServerDisConnection();

private:
    QTcpServer                         *m_tcpServer;
    SocketIndividual                   *m_socket;
    QList<SocketIndividual *>           m_socketList;
    ChannelAttributes                   m_mapAttrs;
};

#endif // TCPSERVERCHANNEL_H
