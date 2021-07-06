#ifndef TESTSERVICE_H
#define TESTSERVICE_H
#include "ICommunicationService.h"
#include "BundleContext.h"
#include "communicationservicebase.h"

#include <QByteArray>
#include <QMap>

using namespace cppmicroservices;

class CommunicationServiceImpl;

class CommunicationService : public QObject, public ICommunicationServiceInterface
{
    Q_OBJECT
public:
    CommunicationService(const QString &path, BundleContext context);
    ~CommunicationService();

    /**
     * @brief sendMessage 发送数据接口
     * @param channelId 通过那个通道发送（配置文件中的id）
     * @param data 要发送的数据
     * @return 发送数据的长度
     */
    int sendMessage(const QString &channelId, const QByteArray &data);
    int sendMessage(const QString &channelId, const QByteArray &data, QString sendIP);

    /**
     * @brief stop 停止服务（停止所有通道线程）
     * @return 无
     */
    void stop();

    /**
     * @brief getBundleContext 获取环境对象
     * @return BundleContext实例
     */
    BundleContext getBundleContext();

    /**
     * @brief getCommunication 获取通道对象
     * @return 成功-返回通道指针；失败-返回NULL；
     */
    CommunicationServiceBase *getCommunication(const QString &channelId);

    void initCommunication();
    CommunicationServiceBase *createChannel(const QDomNode &configNode);
    CommunicationServiceBase *createChannel(const ChannelAttributes &attrs);

    void analysisChildAttr(const QDomNode &configNode, ChannelAttributes &attrs);
    void analysisAttr(const QDomNode &configNode, ChannelAttributes &attrs);
private:
    BundleContext               m_context;

    QMap<QString, CommunicationServiceBase *>      m_channels;
    QString                                        m_configPath;

    CommunicationService                           *m_commnunicationService;
};
#endif  // TESTSERVICE_H
