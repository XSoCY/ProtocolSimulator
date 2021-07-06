/*
 * TCP通道:此类主要创建TCP客户端通讯通道
 * 创建者：zengl
 * 创建日期：2021-03-12
 */
#ifndef TCPCHANNEL_H
#define TCPCHANNEL_H

#include "channelbase.h"
#include <QThread>

class COMMUNICATIONCHANNELSSHARED_EXPORT TcpChannel : public ChannelBase
{
    Q_OBJECT
public:
    TcpChannel(const ChannelAttributes &attrs, QObject *parent = nullptr);
    ~TcpChannel();

    /**
     * @brief init  根据通道参数，初始化通道
     * @return 无
     */
    bool init();

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

public slots:
    /**
     * @brief receiveData  接收数据槽函数
     * @return 无
     */
    void receiveData();

    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    int sendDataLot(const QByteArray &data);

    /**
     * @brief onSocketError  网络错误槽函数
     * @return 无
     */
    void onSocketError(QAbstractSocket::SocketError error);

    /**
     * @brief onDisconnected 断开连接槽函数
     * @return 无
     */
    void onDisconnected();

    /**
     * @brief onTcpClientReConnect TCP重连槽函数
     * @return 无
     */
    void onTcpClientReConnect();

private:
    //TCP socket
    QTcpSocket      *m_tcpSocket;

    QTimer          *m_timer;
};

#endif // TCPCHANNEL_H
