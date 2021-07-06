/*
 * COMM通道:此类主要创建串口通讯通道
 * 创建者：xuejh
 * 创建日期：2021-01-22
 */
#ifndef COMMCHANNEL_H
#define COMMCHANNEL_H

#include "channelbase.h"
#include <QtSerialPort/QSerialPort>

class COMMUNICATIONCHANNELSSHARED_EXPORT CommChannel: public ChannelBase
{
    Q_OBJECT
public:
    CommChannel(const ChannelAttributes &attrs, QObject *parent = nullptr);

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

public:
    QSerialPort         *m_serialPort;
};

#endif // COMMCHANNEL_H
