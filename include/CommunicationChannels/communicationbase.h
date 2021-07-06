#ifndef COMMUNICATIONBASE_H
#define COMMUNICATIONBASE_H

#include <QThread>
#include "channelbase.h"
#include "udpchannel.h"
#include "commchannel.h"
#include "tcpchannel.h"
#include "tcpserverchannel.h"

class CommunicationService;

class COMMUNICATIONCHANNELSSHARED_EXPORT CommunicationBase : public QThread
{
    Q_OBJECT
public:
    CommunicationBase(const ChannelAttributes &attrs, QObject *parent=nullptr);

    void stop();

    void setCreateHandle(_createCallback f);

    _createCallback getHandle();
    /**
     * @brief getAttr  获取通道参数
     * @param key     参数的key值
     * @return 无
     */
    virtual QString getAttr(const QString &key);

    /**
     * @brief getAttr  获取全部通道参数
     * @return 通道参数数据
     */
    virtual ChannelAttributes getAttr();

    /**
     * @brief getConnectState  获取通道状态
     * @return 通道状态
     */
    virtual QAbstractSocket::SocketState getConnectState();

    /**
     * @brief getConnectError  获取通道状态
     * @return 通道状态
     */
    virtual QAbstractSocket::SocketError getConnectError();

    /**
     * @brief delMessage 当缓冲区数据量比较大时，删除缓冲区数据（从头往后删，先入先删）
     * @param count 删除数量，当数量为0时，删除index后的所有数据
     * @param index 从某个点开始删除，默认从头开始
     * @return 无
     */
    virtual bool delMessage(int count=0, int index=0);

    /**
     * @brief getMessage  获取缓冲区的数据（先入后出顺序）
     * @return 有则返回MessageSharePointer，否则返回NULL
     */
    virtual MessageSharePointer getMessage();

    /**
     * @brief getMessageCount  获取消息数量
     * @return 消息数量
     */
    virtual int getMessageCount();

    /**
     * @brief closeChannel  关闭通道，由继承者实现
     * @return 消息数量
     */
    virtual void closeChannel();

    /**
     * @brief getSendCount  获取已发送的数据量
     * @return 已发送数据长度
     */
    virtual uint getSendCount();

    /**
     * @brief getSendCount  获取已接收的数据量
     * @return 已接收数据长度
     */
    virtual uint getReveiveCount();

    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    virtual int sendData(const QByteArray &data);

    /**
     * @brief sendData 发送数据接口
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    virtual int sendData(const QByteArray &data, QString ip);

protected:
    void run();

signals:
    void signalSend(const QByteArray data);
    void tcpSignalSend(const QByteArray data, QString ip);

protected:
    bool                    m_running;

    ChannelBase             *m_channel;
    ChannelAttributes       m_attrs;

    int                     m_timingCall;               //定时时间（毫秒），由配置文件配置
    _createCallback         m_fun;
};

#endif // COMMUNICATIONBASE_H
