#include "commchannel.h"
#include "log.h"

CommChannel::CommChannel(const ChannelAttributes &attrs, QObject *parent)
    : ChannelBase(attrs, parent)
    , m_serialPort(NULL)
{
    init();
}

bool CommChannel::init()
{
    bool bret = false;

    if( !m_serialPort )
    {
        m_serialPort = new QSerialPort();
    }
    else
    {
        if( m_serialPort->isOpen() ) //如果串口已经打开了 先给他关闭了
        {
            m_serialPort->clear();
            m_serialPort->close();
        }
    }


    //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
    QString ProtName = getAttr(CHANNEL_COMM_NAME);
    m_serialPort->setPortName(ProtName);
    //用ReadWrite 的模式尝试打开串口
    if( !m_serialPort->open(QIODevice::ReadWrite) )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), "comm open fail: "+m_serialPort->errorString());

        m_serialPort->close();
        m_serialPort = NULL;

        return false;
    }

    m_serialPort->setBaudRate(getAttr(CHANNEL_COMM_BAUDRATE).toInt());  //设置波特率和读写方向
    m_serialPort->setDataBits((QSerialPort::DataBits)getAttr(CHANNEL_COMM_DATABITS).toInt());          //数据位为8位
    m_serialPort->setFlowControl((QSerialPort::FlowControl)getAttr(CHANNEL_COMM_FLOWCONTROL).toInt());    //无流控制
    m_serialPort->setParity((QSerialPort::Parity)getAttr(CHANNEL_COMM_PARITY).toInt());              //无校验位
    m_serialPort->setStopBits((QSerialPort::StopBits)getAttr(CHANNEL_COMM_STOPBITS).toInt());          //一位停止位

    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个readyRead信号,我们定义个槽void receiveData()解析数据
    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveData()));

    return true;
}

void CommChannel::closeChannel()
{
    if( m_serialPort && m_serialPort->isOpen() )
    {
        m_serialPort->close();
        m_serialPort = nullptr;
    }
    else m_serialPort = nullptr;
}

int CommChannel::sendData(const QByteArray &data)
{
    return sendData(data.data(), data.length());
}

int CommChannel::sendData(const char *data, int len)
{
    if( m_serialPort ) return m_serialPort->write(data, len);

    return 0;
}

void CommChannel::waitForReadyRead()
{
    int itimeout = 0;

    itimeout = getAttr(CHANNEL_TIME_OUT).toInt();
    itimeout = (itimeout > 0 ? itimeout : 30000); //默认值为30000

    if( m_serialPort ) m_serialPort->waitForReadyRead(itimeout);
}

void CommChannel::receiveData()
{
    m_serialPort->waitForReadyRead(10);
    QByteArray bytes = m_serialPort->readAll();

    qDebug() << bytes.toHex();

    if( !bytes.isEmpty() ) addMessage(bytes);
}

int CommChannel::sendDataLot(const QByteArray &data)
{
    return sendData(data);
}

