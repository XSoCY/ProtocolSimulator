#include "SystemGraphicsView.h"

#include <QImageWriter>

#include <QFile>
#include <QDebug>
#include <QDomDocument>

#include "log.h"

SystemGraphicsView::SystemGraphicsView(QWidget* parent) : CBaseGraphicsView(parent)
{
    qDebug() << "SystemGraphicsView::SystemGraphicsView";

    m_width = 1920;
    m_height = 1600;

    initLinkConfig();

    init();

    //光切换模式初始化
    QString optModId("lightMatrixModeCombobox");
    int switchState = GetGraphicSwitchState(optModId);
    lightMatrixModeChange(switchState);
}

/**
 * @brief createDiagramData 创建视图数据
 */
void SystemGraphicsView::createDiagramData()
{

}

/**
 * @brief setEntityEnable   设置实体使能
 * @param bEnable   true：使能 false:不使能
 */
void SystemGraphicsView::setEntityEnable(bool bEnable)
{
    QString strID;
    strID = QString("lightMatrixModeCombobox");
    setGraphicsEnable(strID, bEnable);

    strID = QString("testSwitchControlCombobox");
    setGraphicsEnable(strID, false);

    for(int i = 1; i < 9; i++)
    {
        QString strID = QString("lightMatrixCheckOptionCombobox%1").arg(i);
        setGraphicsEnable(strID, bEnable);
    }
    for(int i = 1; i < 11; i++)
    {
        QString strID = QString("lightMatrixCompositeOptionCombobox%1").arg(i);
        setGraphicsEnable(strID, bEnable);
    }
    for(int i = 1; i < 7; i++)
    {
        QString strID = QString("midFrequencyOptionComboBox%1").arg(i);
        setGraphicsEnable(strID, bEnable);
    }
    for(int i = 1; i < 3; i++)
    {
        QString strID = QString("sFrequencyOptionCombobox%1").arg(i);
        setGraphicsEnable(strID, bEnable);
    }
    for(int i = 1; i < 3; i++)
    {
        QString strID = QString("lFrequencyOptionCombobox%1").arg(i);
        setGraphicsEnable(strID, bEnable);
    }
    for(int i = 1; i < 2; i++)
    {
        QString strID = QString("sixOptionOneCombobox");
        setGraphicsEnable(strID, bEnable);
    }
}

/**
 * @brief lightMatrixModeChange     光切换矩阵模式改变
 * @param index 模式索引
 */
void SystemGraphicsView::lightMatrixModeChange(int index)
{
    QString strID;
    if(index < 0)
    {
        return ;
    }
    strID = QString("lightMatrixModeCombobox");
    this->SetGraphicsSwitchState(strID, index);
    //隐藏相关连接线
    for(auto oneKey : m_mapConnectId.keys()){
        QStringList tmpList = m_mapConnectId.value(oneKey);
        for(auto strId : tmpList){
            this->setGraphicsVisible(strId, false);
        }
    }
    switch(index)
    {
    // 任务模式
    case 0:
        for(int i = 1; i < 6; i++)
        {
            QString text = QString("1&2,3&4,5&6,7&8,1&2(备),3&4(备),5&6(备),7&8(备)");
            strID = QString("lightMatrixCompositeOptionCombobox%1").arg(i);
            this->setEntityText(strID, text, (i - 1));
        }
        for(int i = 1; i < 5; i++)
        {
            QString text = QString("1&2,3&4,5&6,7&8");
            strID = QString("lightMatrixCheckOptionCombobox%1").arg(i);
            this->setEntityText(strID, text, i - 1);
        }

        break;
        // 回放模式
    case 1:
        for(int i = 1; i < 5; i++)
        {
            QString text = QString("1,2,3,4,5");
            strID = QString("lightMatrixCheckOptionCombobox%1").arg(i);
            this->setEntityText(strID, text, i - 1);
        }
        break;
        // 自检模式
    case 2:
        for(int i = 1; i < 6; i++)
        {
            QString text = QString("1,2,3,4,5");
            strID = QString("lightMatrixCompositeOptionCombobox%1").arg(i);
            this->setEntityText(strID, text, (i - 1));
        }
        break;
    }
    //显示对应模式的连接线
    uchar optMod = index +1;
    QStringList modListId = m_mapConnectId.value(optMod);
    for(auto oneKey  : modListId){
        this->setGraphicsVisible(oneKey, true);
    }
}

/**
 * @brief setLightConfigData 设置光切换矩阵配置数据
 * @param lightdata     光切换矩阵参数数据
 */
void SystemGraphicsView::setLightConfigData(QByteArray& lightdata)
{

}

/**
 * @brief setLightConfigData 设置测试开关网络配置数据
 * @param testdata      测试开关网络参数数据
 */
void SystemGraphicsView::setTestConfigData(QByteArray& testdata)
{

}

/**
 * @brief initLinkConfig    初始化链路资源配置数据/System/LxTsspConfig/LinkResourceConfig.xml
 */
bool SystemGraphicsView::initLinkConfig()
{
    return true;
}

void SystemGraphicsView::addModWithConnecID(const uint &mod, const QStringList &strIds)
{
    QStringList currentIds = m_mapConnectId.value(mod);
    currentIds.append(strIds);
    m_mapConnectId.insert(mod, currentIds);
}

EntityShape SystemGraphicsView::addStreamTextToComposite(const EntityShape &shapeOne,
                                                         const QPoint& oripoint,
                                                         const QString &stream)
{
    QPoint lefttopPos =oripoint;

    EntityShape textshape;
    textshape.id = QString("dddd");
    textshape.type = Text;
    textshape.pos = QPoint(lefttopPos.x(), lefttopPos.y());
    textshape.width = 2*LINE_SPACE;
    textshape.height = 2*LINE_SPACE;
    textshape.text = stream;
    textshape.zValue = shapeOne.zValue;
    return textshape;

}
