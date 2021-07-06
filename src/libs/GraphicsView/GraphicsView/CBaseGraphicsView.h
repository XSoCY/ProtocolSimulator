#ifndef CBASEGRAPHICSVIEW_H
#define CBASEGRAPHICSVIEW_H

/*********************** CBaseGraphicsView  视图基类  ***************************/

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QVector>

#include "graphicsview_global.h"
#include "DiagramCommonDefine.h"
#include "CBaseGraphicsItemGroup.h"

class CBaseGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CBaseGraphicsView(QWidget* parent = 0);

    /**
     * @brief SetGraphicsColor 设置系统框图状态颜色
     * @param strID     项ID
     * @param strColor  颜色字符串
     */
    void SetGraphicsColor(QString strID, QString strColor);

    /**
     * @brief SetGraphicsShape  重新绘制和差开关按钮,返回设置完后开关的状态
     * @param strID     项ID
     * @return  开关状态
     */
    int SetGraphicsShape(QString strID);

    /**
     * @brief setGraphicsText 设置视图线文本
     * @param strID     项ID
     * @param text      文本
     */
    void setGraphicsText(QString strID, LineText text);

    /**
     * @brief setGraphicsEnable 设置视图是否启用
     * @param strID     项ID
     * @param bEnable   true:启用 false:不启用
     */
    void setGraphicsEnable(QString strID, bool bEnable);

    /**
     * @brief setGraphicsVisible 设置视图项是否可见
     * @param strID     项ID
     * @param visible   true:可见 false:不可见
     */
    void setGraphicsVisible(QString strID, bool visible);

    /**
     * @brief setEntityText 设置实体文本
     * @param strID 项ID
     * @param text  文本
     * @param textRows  文本行数
     */
    void setEntityText(QString strID, QString text, int textRows);

    /**
     * @brief SetGraphicsSwitchState    设置开关状态
     * @param strID         项ID
     * @param switchState   开关状态
     */
    void SetGraphicsSwitchState(QString strID, int switchState);

    /**
     * @brief GetGraphicSwitchState     获得开关状态
     * @param strID         项ID
     * @return      开关状态
     */
    int GetGraphicSwitchState(QString strID);

    /**
     * @brief GetGraphicConnectorShape     获得连接形状数据
     * @param strID         项ID
     * @return              连接形状
     */
    ConnectorShape GetGraphicConnectorShape(QString strID);

    /**
     * @brief GetGraphicConnectorShape     获得实体形状数据
     * @param strID         项ID
     * @return              实体形状
     */
    EntityShape GetGraphicEntityShape(QString strID);

    /**
     * @brief GetAllEntityIDList    获得所有实体ID列表
     * @return      所有实体ID列表
     */
    QList<QString> GetAllEntityIDList()
    {
        return m_pMapEntityGroups.keys();
    }

    /**
     * @brief getLeftEdge   获得左边距
     * @return
     */
    static int getLeftEdge();
    /**
     * @brief getRightEdge  获得右边距
     * @return
     */
    static int getRightEdge();
    /**
     * @brief getTopEdge    获得上边距
     * @return
     */
    static int getTopEdge();
    /**
     * @brief getBottomEdge 获得下边距
     * @return
     */
    static int getBottomEdge();

protected:
    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent *event);

protected:

    /**
     * @brief createDiagramData 创建图形数据
     */
    virtual void createDiagramData();

    /**
     * @brief init  初始化 配置Sence和View的属性
     */
    void init();

    /**
     * @brief setDiagramData    设置图形数据
     * @param rectVector        区域容器
     * @param connectorVector   连接容器
     */
    void setDiagramData(QVector<EntityShape> rectVector, QVector<ConnectorShape> connectorVector);

    /**
     * @brief setConnectorData  设置连接数据
     * @param connector         连接形状
     * @param pItemGroupBase    组项基类
     */
    void setConnectorData(ConnectorShape connector, CBaseGraphicsItemGroup* pItemGroupBase);

    /**
     * @brief setEntityData     设置实体数据，添加组项到场景，缓存组项Map
     * @param entityShape       实体形状对象
     * @param pItemGroupBase    组项基类
     */
    void setEntityData(EntityShape entityShape, CBaseGraphicsItemGroup* pItemGroupBase);

    /**
     * @brief setWidgetData     设置窗体数据
     * @param entityShape       实体形状对象
     * @param pItemGroupBase    组项基类
     */
    void setWidgetData(EntityShape entityShape, CBaseGraphicsItemGroup* pItemGroupBase);

signals:
    /**
     * @brief signal_doubleClick  实体双击，显示视图信号
     * @param
     */
    void signal_doubleClick(QString);
    /**
     * @brief signal_singleClick  实体双击，显示视图信号
     * @param
     */
    void signal_singleClick(QString);
    /**
     * @brief sig_switch    开关信号
     */
    void sig_switch(QString);

protected:
    QGraphicsScene* m_pScene;

    // QString = 图形ID CItemGroupBase*=图形指针
    //用来存储框图中的每一项图形，将来以此实时操作图形状态
    QMap<QString, CBaseGraphicsItemGroup*> m_pMapItemGroups;

    //用来存储框图中的每一项实体
    QMap<QString, CBaseGraphicsItemGroup*> m_pMapEntityGroups;

    qreal m_scale;        // 当前比例

    bool m_bDrag;

    QPointF m_sourcePoint;
    QPointF m_destinationPoint;
    QPointF m_CenterPoint;
    QPoint m_mouseLBtnDown;
    QRectF m_SceneRect;

    static int m_width;   //框图宽度
    static int m_height;  //框图长度
};

#endif // CBASEGRAPHICSVIEW_H
