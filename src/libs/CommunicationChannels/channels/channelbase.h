/*
 * 通道基础类，处理配置解析和获取等，所有的通讯通道继承此类
 * 创建者：xuejh
 * 创建日期：2020-12-09
 */
#ifndef CHANNELBASE_H
#define CHANNELBASE_H

#include "communicationchannels_global.h"

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include <QMutex>
#include <QSharedPointer>
#include <QtNetwork>

#define CHANNEL_NODE_NAME           "channel"
#define CHANNEL_ID                  "id"
#define CHANNEL_DESC                "desc"
#define CHANNEL_TYPE                "type"
#define CHANNEL_TIMINGCALL          "timingcall"
#define CHANNEL_TIME_OUT            "timeout"

// TCP & UDP通讯参数
#define CHANNEL_LOCAL_IP            "localip"
#define CHANNEL_LOCAL_PORT          "localport"
#define CHANNEL_REMOTE_IP           "remoteip"
#define CHANNEL_REMOTE_PORT         "remoteport"

//串口通讯参数
#define CHANNEL_COMM_NAME           "name"
#define CHANNEL_COMM_BAUDRATE       "baudrate"
#define CHANNEL_COMM_DATABITS       "databits"
#define CHANNEL_COMM_FLOWCONTROL    "slowsontrol"
#define CHANNEL_COMM_PARITY         "sarity"
#define CHANNEL_COMM_STOPBITS       "stopsits"

class ChannelBaseImpl;

enum ChannelType
{
    CHANNEL_TYPE_NONE               = 0, //无
    CHANNEL_TYPE_TCP_CLIENT         = 1, //TCP客户端
    CHANNEL_TYPE_TCP_SERVER         = 2, //TCP服务端
    CHANNEL_TYPE_UDP_P2P            = 3, //UDP点对点
    CHANNEL_TYPE_UDP_MULTICAST      = 4, //UDP组播
    CHANNEL_TYPE_UDP_BROADCAST      = 5, //UDP广播
    CHANNEL_TYPE_COMM               = 6, //串口通讯
};

//属性map定义
typedef QMap<QString, QString>          ChannelAttributes;
//属性迭代器
typedef ChannelAttributes::iterator     ChannelAttributesIterator;
//消息的智能指针
typedef QSharedPointer<QByteArray>      MessageSharePointer;

class SocketIndividual;
typedef std::function<SocketIndividual*(QTcpSocket *, const ChannelAttributes &)> _createCallback;

class COMMUNICATIONCHANNELSSHARED_EXPORT ChannelBase : public QObject
{
    Q_OBJECT
public:
    ChannelBase(const ChannelAttributes &attrs, QObject *parent);
    ~ChannelBase();

    /**
     * @brief setChannelAttr  设置通道参数
     * @param attrs     通道参数数据，map形式，具体的值与上面一个函数一致
     * @return 无
     */
    virtual void setChannelAttr(const ChannelAttributes &attrs);

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
     * @brief setConnectState  设置通道状态
     * @param state 通道状态
     * @return 无
     */
    virtual void setConnectState(QAbstractSocket::SocketState state);

    /**
     * @brief getConnectState  获取通道状态
     * @return 通道状态
     */
    virtual QAbstractSocket::SocketState getConnectState();

    /**
     * @brief setConnectError  设置通道状态
     * @param state 通道状态
     * @return 无
     */
    virtual void setConnectError(QAbstractSocket::SocketError error);

    /**
     * @brief getConnectError  获取通道状态
     * @return 通道状态
     */
    virtual QAbstractSocket::SocketError getConnectError();

    /**
     * @brief addMessage  添加接收到的数据到缓冲区
     * @param msg 接收到的数据
     * @return 无
     */
    virtual bool addMessage(const QByteArray &msg);

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
    virtual void closeChannel() = 0;

    /**
     * @brief SendData  发送数据，由继承者实现
     * @param data 要发送的数据
     * @return 发送数据长度
     */
    virtual int sendData(const QByteArray &data) = 0;

    /**
     * @brief SendData  发送数据，由继承者实现
     * @param data 要发送的数据
     * @param len 数据长度
     * @return 发送数据长度
     */
    virtual int sendData(const char *data, int len) = 0;

    /**
     * @brief addSendCount  增加发送数据的长度
     * @param len 数据长度
     * @return 发送数据长度
     */
    virtual void addSendCount(int len);

    void addReceiveCount(int len);

    /**
     * @brief getChannelType  获取通道类型
     * @return 通道类型，0-未知；1-TCP客户端；2-TCP服务端；3-UDP点对点；4-UDP组播；5-UDP广播
     */
    virtual ChannelType getChannelType();

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
     * @brief waitForReadyRead 等待ReadyRead信号，由继承类实现
     * @return 无
     */
    virtual void waitForReadyRead() = 0;

    virtual void setHandlePtr(_createCallback f){}
private:
    QAbstractSocket::SocketState                m_connectState;
    QAbstractSocket::SocketError                m_connectError;
    ChannelAttributes                           m_mapAttrs;

    QList<QSharedPointer<QByteArray>>           m_messageQueue;
    QMutex                                      m_messageMutex;  //消息互斥

    uint                                        m_receiveCount;
    uint                                        m_sendCount;
};

#endif // UDPCHANNEL_H
