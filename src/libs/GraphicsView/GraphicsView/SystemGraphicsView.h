#ifndef SYSTEMGRAPHICSVIEW_H
#define SYSTEMGRAPHICSVIEW_H

/*********************** SystemGraphicsView  系统框图类  ***************************/

#include <QObject>

#include "graphicsview_global.h"
#include "DiagramCommonDefine.h"
#include "CBaseGraphicsView.h"

#define BLUECOLOR       "#1EB4E6"           // 可编辑颜色 蓝色
#define GREENCOLOR      "#00AF50"           // 正常状态   绿色
#define YELLOWCOLOR     "yellow"            // 占用      黄色
#define LIGHTGRAYCOLOR  "#C0C0C0"           // 离线      灰色
#define REDCOLOR        "#FF0000"           // 故障      红色

#pragma pack(1)

/**
 * @brief Resource 资源结构体
 */
struct LinkResource{
    uint resourceId;    // 资源ID
    char sn;            // 流号
    QString text;       // 链路资源名称
    QString ObjectID;   // 需要显示界面的对象ID

    LinkResource()
    {
        resourceId = 0;
        sn = 0;
    }
    QString getKey()
    {
        return QString::number(resourceId, 16) + QString::number(sn, 16);
    }
};

#pragma pack()

class SystemGraphicsView : public CBaseGraphicsView
{
    Q_OBJECT
public:
    SystemGraphicsView(QWidget* parent = 0);

    /**
     * @brief getSystemPixmap 获得系统图片
     * @return
     */
    const QPixmap& getSystemPixmap()
    {
        return m_pixmap;
    }

    /**
     * @brief getLinkResource 获得链路资源
     * @return
     */
    const QMap<QString, LinkResource>& getLinkResource()
    {
        return m_ResourceMap;
    }

    /**
     * @brief setLightConfigData 设置光切换矩阵配置数据
     * @param lightdata     光切换矩阵参数数据
     */
    void setLightConfigData(QByteArray& lightdata);
    /**
     * @brief setLightConfigData 设置测试开关网络配置数据
     * @param testdata      测试开关网络参数数据
     */
    void setTestConfigData(QByteArray& testdata);

    /**
     * @brief setEntityEnable   设置实体使能
     * @param bEnable   true：使能 false:不使能
     */
    void setEntityEnable(bool bEnable);

    /**
     * @brief lightMatrixModeChange     光切换矩阵模式改变
     * @param index 模式索引
     */
    void lightMatrixModeChange(int index);

private:
    virtual void createDiagramData();

    /**
     * @brief initLinkConfig    初始化链路资源配置数据/System/LxTsspConfig/LinkResourceConfig.xml
     */
    bool initLinkConfig();

    //增加模式和对应的连接id
    void addModWithConnecID(const uint& mod, const QStringList& strIds);

    //综合基带添加流
    EntityShape compositeBaseRect1;

    EntityShape addStreamTextToComposite(const EntityShape& shapeOne, const QPoint& oripoint, const QString& stream);
private:

//    void createDiagramKaSendData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createDiagramKaRecvData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createDiagramSSendAndRecvData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createDiagramXRecvData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createMonitorESData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createTimeFrequencyESData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createTestCalibrationESData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

//    void createHealthManagementESData(QVector<EntityShape>& rectVector, QVector<ConnectorShape>& connectorVector);

private:
    QPixmap m_pixmap;

    /**
     * @brief m_ResourceMap 资源QMap<资源名称， 资源信息>
     */
    QMap<QString, LinkResource> m_ResourceMap;
    //模式的连接线id 《模式，连接线ids》
    QMap<uchar, QStringList> m_mapConnectId;
};

#endif // SYSTEMGRAPHICSVIEW_H
