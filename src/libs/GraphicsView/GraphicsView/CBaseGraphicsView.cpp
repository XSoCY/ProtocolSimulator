#include "CBaseGraphicsView.h"


#include "CRectItemGroup.h"
#include "CTextItemGroup.h"
#include "CArrowLineItemGroup.h"
#include "CComboBoxItemGroup.h"

int CBaseGraphicsView::m_width = 0;
int CBaseGraphicsView::m_height = 0;

#define SCENE 1

CBaseGraphicsView::CBaseGraphicsView(QWidget* parent) : QGraphicsView(parent)
{
    m_scale = 1;
    m_bDrag = false;
    m_pMapItemGroups.clear();
    m_pMapEntityGroups.clear();
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
/**
 * @brief init  初始化 配置Sence和View的属性
 */
void CBaseGraphicsView::init()
{
    qDebug() << "CBaseGraphicsView::init";

    m_pScene = new QGraphicsScene(this);
    m_pScene->setBackgroundBrush(Qt::white);
    setScene(m_pScene);
    setRenderHints(QPainter::Antialiasing);
    m_CenterPoint.setX(-m_width / 2);
    m_CenterPoint.setY(-m_height / 2);
    m_SceneRect.setRect(0, 0, m_width, m_height);
    m_pScene->setSceneRect(m_SceneRect);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setCacheMode(QGraphicsView::CacheBackground);
    setScene(m_pScene);
    centerOn(m_CenterPoint);
    this->scale(0.6, 0.6);
    createDiagramData();

}

void CBaseGraphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug() << QString("CBaseGraphicsView::mousePressEvent:QPoint(%1, %2)").arg(event->pos().rx()).arg(event->pos().ry());
    QCursor sursor;
    sursor.setShape(Qt::OpenHandCursor);
    this->setCursor(sursor);
    if(event->button() == Qt::LeftButton)
    {
        if(scene()->itemAt(mapToScene(event->pos()), transform()) == nullptr)
        {
            m_mouseLBtnDown = event->pos();
            m_sourcePoint = event->pos();
            m_bDrag = true;
        }
    }
}

void CBaseGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
#ifdef SCENE
    if(m_bDrag)
    {
        QCursor sursor;
        sursor.setShape(Qt::ClosedHandCursor);
        this->setCursor(sursor);
/*
        QPointF ptNow = mapToScene(event->pos());
        QPointF movePt = ptNow - mapToScene(m_mouseLBtnDown);
        m_SceneRect.setX(- movePt.x());
        m_SceneRect.setY(- movePt.y());
        scene()->setSceneRect(m_SceneRect);
        //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//        m_CenterPoint.setX(m_CenterPoint.x() - movePt.x());
//        m_CenterPoint.setX(m_CenterPoint.y() - movePt.y());
//        centerOn(m_CenterPoint);
//        setScene(m_pScene);
//        this->update();
//        m_pScene->update();
        //setTransformationAnchor(QGraphicsView::AnchorViewCenter);
*/
    }
#else
    if(m_bDrag)
    {
        QCursor sursor;
        sursor.setShape(Qt::ClosedHandCursor);
        this->setCursor(sursor);
        m_destinationPoint = event->pos();
        QPoint disPoint(m_destinationPoint.x() - m_sourcePoint.x(), m_destinationPoint.y()- m_sourcePoint.y());
        QRectF sceneRect = m_pScene->sceneRect();
        qDebug() << QString("CBaseGraphicsView::mouseReleaseEvent起点:QPoint(%1, %2)终点：QPoint(%3, %4)偏移：QPoint(%5, %6)")
                    .arg(m_sourcePoint.rx()).arg(m_sourcePoint.ry())
                    .arg(m_destinationPoint.rx()).arg(m_destinationPoint.ry())
                    .arg(disPoint.rx()).arg(disPoint.ry());
        m_SceneRect.setRect(sceneRect.x() - disPoint.x(), sceneRect.y() - disPoint.y(), m_width, m_height);
        m_pScene->setSceneRect(m_SceneRect);
        qDebug() << QString("CBaseGraphicsView::mouseReleaseEvent场景:QRect(%1, %2, %3, %4)视图:QRect(%5, %6, %7, %8)")
                    .arg(m_pScene->sceneRect().x()).arg(m_pScene->sceneRect().y())
                    .arg(m_pScene->sceneRect().width()).arg(m_pScene->sceneRect().height())
                    .arg(rect().x()).arg(rect().y())
                    .arg(rect().width()).arg(rect().height());
        m_pScene->update();
        //        m_CenterPoint.setX(m_CenterPoint.x() - disPoint.x());
        //        m_CenterPoint.setX(m_CenterPoint.y() - disPoint.y());
        //        m_pScene->setSceneRect(m_CenterPoint.x(), m_CenterPoint.y(), m_width, m_height);
    }
#endif
}

void CBaseGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    qDebug() << QString("CBaseGraphicsView::mouseReleaseEvent:QPoint(%1, %2)").arg(event->pos().rx()).arg(event->pos().ry());
    QCursor sursor;
    sursor.setShape(Qt::PointingHandCursor);
    this->setCursor(sursor);
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}
// 缩放视图： 按下ctrl键时缩放视图，否则进行滚动
void CBaseGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal scaleValue = 0.2;

    //判断是否按下ctrl键
    if( QApplication::keyboardModifiers() != Qt::ControlModifier )
    {
        //未按下ctrl键
        QGraphicsView::wheelEvent(event);
        return;
    }

    // 放大
    if(event->delta() > 0){
        if(m_scale < 2){
            m_scale *= (1 + scaleValue);
            this->scale(1 + scaleValue, 1 + scaleValue);
        }else{
            m_scale = 2;
            return ;
        }
    }
    // 缩小
    else{
        if(m_scale > 0.2){
            m_scale *= (1 - scaleValue);
            this->scale(1 - scaleValue, 1 - scaleValue);
        }else{
            m_scale = 0.2;
            return ;
        }
    }
    //    m_pScene->setSceneRect(0, 0, m_pScene->sceneRect().width(), m_pScene->sceneRect().height());
}


/**
 * @brief getLeftEdge   获得左边距
 * @return
 */
int CBaseGraphicsView::getLeftEdge()
{
    return 0;
}
/**
 * @brief getRightEdge  获得右边距
 * @return
 */
int CBaseGraphicsView::getRightEdge()
{
    return m_width;
}
/**
 * @brief getTopEdge    获得上边距
 * @return
 */
int CBaseGraphicsView::getTopEdge()
{
    return 0;
}
/**
 * @brief getBottomEdge 获得下边距
 * @return
 */
int CBaseGraphicsView::getBottomEdge()
{
    return m_height;
}

void CBaseGraphicsView::createDiagramData()
{
    qDebug() << "CBaseGraphicsView::createDiagramData";
}

/**
 * @brief setDiagramData    设置图形数据
 * @param rectVector        区域容器
 * @param connectorVector   连接容器
 */
void CBaseGraphicsView::setDiagramData(QVector<EntityShape> entityVector, QVector<ConnectorShape> connectorVector)
{
    qDebug() << "CBaseGraphicsView::setDiagramData";
    //CBaseGraphicsItemGroup* pItemGroupBase;
    // 实体形状遍历
    foreach (EntityShape entity, entityVector)
    {
        CBaseGraphicsItemGroup* pItemGroupBase = NULL;
        switch (entity.type)
        {
            // 矩形
            case Rect:
            {
                pItemGroupBase = new CRectItemGroup();
                connect(pItemGroupBase, SIGNAL(doubleClick(QString)), this, SIGNAL(signal_doubleClick(QString)));
                connect(pItemGroupBase, SIGNAL(singleClick(QString)), this, SIGNAL(signal_singleClick(QString)));

                setEntityData(entity, pItemGroupBase);
                pItemGroupBase->setZValue(entity.zValue);
                break;
            }
    //        case Pixmap:
    //        {
    //            setEntityData(entity, new CPixmapItemGroup());
    //            break;
    //        }
            case Text:
            {
                pItemGroupBase = new CTextItemGroup();
                setEntityData(entity, pItemGroupBase);
                pItemGroupBase->setZValue(entity.zValue);
                break;
            }
    //        case TwoArcCircle:
    //        {
    //            setEntityData(entity, new CTwoArcCircleItemGroup());
    //            break;
    //        }
    //        case IXIItem:
    //        {
    //            setEntityData(entity, new C1X1ItemGroup());
    //            break;
    //        }
    //        case RectCircle:
    //        {
    //            setEntityData(entity, new CRectCircleItemGroup());
    //            break;
    //        }
    //        default:
    //            break;
            case ComboBox:
            {
                pItemGroupBase = new CComboBoxItemGroup();
                connect(pItemGroupBase, SIGNAL(singleClick(QString)), this, SIGNAL(sig_switch(QString)));
                setWidgetData(entity, pItemGroupBase);
                break;
            }
        }
        if(pItemGroupBase != NULL)
        {
            if(entity.bFixed)
            {
                pItemGroupBase->setFlag(QGraphicsItem::ItemIgnoresTransformations);
            }
        }
    }
    // 连接形状遍历
    foreach (ConnectorShape connector, connectorVector)
    {
        switch (connector.type)
        {
        //箭头线
        case ArrowLine:
        {
            setConnectorData(connector, new CArrowLineItemGroup());
            break;
        }
//        //双线圈
//        case DoubleLineCircle:
//        {
//            setConnectorData(connector, new CDoubleLineCircleItemGroup());
//            break;
//        }
//        case FourArrowCircle:
//        {
//            // 重绘开关
//            CFourArrowCircleItemGroup* pThreeArrowCircleItemGroup = new CFourArrowCircleItemGroup();
//            connect(pThreeArrowCircleItemGroup, SIGNAL(doubleClick(QString)), this, SIGNAL(sig_switch(QString)));
//            setConnectorData(connector, pThreeArrowCircleItemGroup);
//            break;
//        }
//        case FourLineCircle:
//        {
//            setConnectorData(connector, new CFourLineCircleItemGroup());
//            break;
//        }
//        case ThreeArrowCircle:
//        {
//            // 重绘开关
//            CThreeArrowCircleItemGroup* pThreeArrowCircleItemGroup = new CThreeArrowCircleItemGroup();
//            connect(pThreeArrowCircleItemGroup, SIGNAL(doubleClick(QString)), this, SIGNAL(sig_switch(QString)));
//            setConnectorData(connector, pThreeArrowCircleItemGroup);
//            break;
//        }
//        case ThreeLineMiddleX:
//        {
//            setConnectorData(connector, new CThreeLineMiddleXItemGroup());
//            break;
//        }
//        case WideArrow:
//        {
//            setConnectorData(connector, new CWideArrowItemGroup());
//            break;
//        }
//        case TwoLineTriang:
//        {
//            setConnectorData(connector, new CTwoLineTriangItemGroup());
//            break;
//        }
//        case TwoLineCircleRect:
//        {
//            setConnectorData(connector, new CTwoLineCircleRectItemGroup());
//            break;
//        }
//        case FourArrowSelfCheck:
//        {
//            setConnectorData(connector, new CFourArrowSelfCheckItemGroup());
//            break;
//        }
//        case ThreeArrowSelfCheck:
//        {
//            setConnectorData(connector, new CThreeArrowCircleItemGroup());
//            break;
//        }
//        case TwoLineRect:
//        {
//            setConnectorData(connector, new CTwoLineRectItemGroup());
//            break;
//        }
//        case ThreeArrowCircleLoad:
//        {
//            // 重绘开关
//            CThreeArrowLoadItemGroup* pThreeArrowCircleItemGroup = new CThreeArrowLoadItemGroup();
//            connect(pThreeArrowCircleItemGroup, SIGNAL(doubleClick(QString)), this, SIGNAL(sig_switch(QString)));
//            setConnectorData(connector, pThreeArrowCircleItemGroup);
//            break;
//        }
        default:
            break;
        }
    }
}

/**
 * @brief setConnectorData  设置连接数据
 * @param connector         连接形状
 * @param pItemGroupBase    组项基类
 */
void CBaseGraphicsView::setConnectorData(ConnectorShape connector, CBaseGraphicsItemGroup* pItemGroupBase)
{
    if (pItemGroupBase->setConnectorData(connector))
    {
        pItemGroupBase->setZValue(0);
        m_pScene->addItem(pItemGroupBase);
        m_pMapItemGroups.insert(connector.id, pItemGroupBase);
    }
}

/**
 * @brief setEntityData     设置实体数据，添加组项到场景，缓存组项Map
 * @param entityShape       实体形状对象
 * @param pItemGroupBase    组项基类
 */
void CBaseGraphicsView::setEntityData(EntityShape entityShape, CBaseGraphicsItemGroup* pItemGroupBase)
{
    if (pItemGroupBase->setEntityData(entityShape))
    {
        m_pScene->addItem(pItemGroupBase);
        m_pMapItemGroups.insert(entityShape.id, pItemGroupBase);
        m_pMapEntityGroups.insert(entityShape.id, pItemGroupBase);
    }
}

/**
 * @brief setWidgetData     设置窗体数据
 * @param entityShape       实体形状对象
 * @param pItemGroupBase    组项基类
 */
void CBaseGraphicsView::setWidgetData(EntityShape entityShape, CBaseGraphicsItemGroup* pItemGroupBase)
{
    m_pScene->addItem(pItemGroupBase);
    pItemGroupBase->setZValue(entityShape.zValue);
    if (pItemGroupBase->setEntityData(entityShape))
    {
        m_pMapItemGroups.insert(entityShape.id, pItemGroupBase);
    }
}

/**
 * @brief SetGraphicsColor 设置系统框图状态颜色
 * @param strID     项ID
 * @param strColor  颜色字符串
 */
void CBaseGraphicsView::SetGraphicsColor(QString strID, QString strColor)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->setBrush(QBrush(QColor(strColor)));
                pItemGroupBase->update();
            }
        }
    }
}

/**
 * @brief SetGraphicsShape  重新绘制和差开关按钮,返回设置完后开关的状态
 * @param strID     项ID
 * @return  开关状态
 */
int CBaseGraphicsView::SetGraphicsShape(QString strID)
{
    int switchState = 0;
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                switchState = pItemGroupBase->changeSwitch();
                pItemGroupBase->update();
            }
        }
    }
    return switchState;
}

/**
 * @brief SetGraphicsSwitchState    设置开关状态
 * @param strID         项ID
 * @param switchState   开关状态
 */
void CBaseGraphicsView::SetGraphicsSwitchState(QString strID, int switchState)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->SetSwitchState(switchState);
                pItemGroupBase->update();
            }
        }
        else
        {
            //未找到实体对象
            qDebug() << QString("未找到开关实体：%1").arg(strID);
        }
    }
}

/**
 * @brief GetGraphicSwitchState     获得开关状态
 * @param strID         项ID
 * @return      开关状态
 */
int CBaseGraphicsView::GetGraphicSwitchState(QString strID)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                int switchState = pItemGroupBase->GetSwitchState();
                return switchState;
            }
        }
    }
    return 0;
}

/**
 * @brief GetGraphicConnectorShape     获得连接形状数据
 * @param strID         项ID
 * @return              连接形状
 */
ConnectorShape CBaseGraphicsView::GetGraphicConnectorShape(QString strID)
{
    ConnectorShape connectShape;
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                connectShape = pItemGroupBase->GetConnectorData();
                return connectShape;
            }
        }
    }
    return connectShape;
}

/**
 * @brief GetGraphicConnectorShape     获得实体形状数据
 * @param strID         项ID
 * @return              实体形状
 */
EntityShape CBaseGraphicsView::GetGraphicEntityShape(QString strID)
{
    EntityShape entityShape;
//    if (!m_pMapItemGroups.isEmpty())
//    {
//        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
//        if (m_pMapItemGroups.end() != iter)
//        {
//            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
//            if (NULL != pItemGroupBase)
//            {
//                entityShape = pItemGroupBase->GetEntityData();
//                return entityShape;
//            }
//        }
//    }
    if (!m_pMapEntityGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapEntityGroups.find(strID);
        if (m_pMapEntityGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                entityShape = pItemGroupBase->GetEntityData();
                return entityShape;
            }
        }
    }
    return entityShape;
}

/**
 * @brief setGraphicsText 设置视图线文本
 * @param strID     项ID
 * @param text      文本
 */
void CBaseGraphicsView::setGraphicsText(QString strID, LineText text)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->setText(text);
                pItemGroupBase->update();
            }
        }
    }
}

/**
 * @brief setEntityText 设置实体文本
 * @param strID 项ID
 * @param text  文本
 */
void CBaseGraphicsView::setEntityText(QString strID, QString text, int textRows)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->setText(text, textRows);
                pItemGroupBase->update();
            }
        }
    }
}

/**
 * @brief setGraphicsEnable 设置视图是否启用
 * @param strID     项ID
 * @param bEnable   true:启用 false:不启用
 */
void CBaseGraphicsView::setGraphicsEnable(QString strID, bool bEnable)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->setEnabled(bEnable);
                pItemGroupBase->update();
            }
        }
    }
}

/**
 * @brief setGraphicsVisible 设置视图项是否可见
 * @param strID     项ID
 * @param visible   true:可见 false:不可见
 */
void CBaseGraphicsView::setGraphicsVisible(QString strID, bool visible)
{
    if (!m_pMapItemGroups.isEmpty())
    {
        QMap<QString, CBaseGraphicsItemGroup*>::iterator iter = m_pMapItemGroups.find(strID);
        if (m_pMapItemGroups.end() != iter)
        {
            CBaseGraphicsItemGroup* pItemGroupBase = iter.value();
            if (NULL != pItemGroupBase)
            {
                pItemGroupBase->setVisible(visible);
                pItemGroupBase->update();
            }
        }
    }
}
