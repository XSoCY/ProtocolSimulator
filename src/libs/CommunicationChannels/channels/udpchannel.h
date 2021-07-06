/*
 * UDP通道:此类主要创建UDP通讯通道，包括点对点、组播、广播
 * 创建者：xuejh
 * 创建日期：2020-12-09
 */
#ifndef UDP_P2P_CHANNEL_H
#define UDP_P2P_CHANNEL_H

#include "channelbase.h"
#include <QThread>

class COMMUNICATIONCHANNELSSHARED_EXPORT UdpChannel : public ChannelBase
{
    Q_OBJECT
public:
    UdpChannel(const ChannelAttributes &attrs, QObject *parent = nullptr);
    ~UdpChannel();

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
     * @brief onSocketError  网络错误槽函数
     * @return 无
     */
    void onSocketError(QAbstractSocket::SocketError error);

    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    int sendDataLot(const QByteArray &data);

protected:
    /**
     * @brief getNetwork  获取当前通道所用IP地址的网卡信息
     * @return 网卡信息（QNetworkInterface）
     */
    QNetworkInterface getNetwork();

private:
    //发送数据socket
    QUdpSocket      *m_udpSendSocket;

    //接收数据socket
    QUdpSocket      *m_udpReceveSocket;
};

#endif // UDPCHANNEL_H
