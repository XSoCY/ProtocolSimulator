#include "carrowpathitem.h"
#include <QDebug>

#define LINE_AND_PIC_SPACE 10

CArrowPathItem::CArrowPathItem(QGraphicsItem *startI, QGraphicsItem *endI, bool isDrawArrow, QGraphicsItem *parent)
    : QGraphicsItem (parent)
    , m_pStartItem(startI)
    , m_pendItem(endI)
    , m_pathItem(new QGraphicsPathItem(this))
    , m_ploygonItem(new QGraphicsPolygonItem(this))
    , m_penColor(Qt::black)
    , m_isDrawArrow(isDrawArrow)
{
    m_pen.setWidth(1);
    m_pen.setColor(m_penColor);

    m_pi = 3.14;

    setFlag(QGraphicsItem::ItemIsSelectable);
}

void CArrowPathItem::getPath(const QPointF &pos1, int width1, int height1, const QPointF &pos2, int width2, int height2, QPainterPath &path)
{
    //此处不考虑图形重合的情况，在这之前会做判断，如果有重合则不调用此代码
    double x = 0;
    double y = 0;
    if( pos1.y() == pos2.y() )
    {//两点在同以水平线上
        getPathForSameY(pos1, width1, height1, pos2, width2, height2, path);
    }
    else if( pos1.x() == pos2.x() )
    {//两点在同一垂直线上
        getPathForSameX(pos1, width1, height1, pos2, width2, height2, path);
    }
    else
    {//其他情况
        getPathForOther(pos1, width1, height1, pos2, width2, height2, path);
    }
}

void CArrowPathItem::getPathForSameX(const QPointF &pos1, int width1, int height1, const QPointF &pos2, int width2, int height2, QPainterPath &path)
{
    if( pos1.y() > pos2.y() )
    {//点2在点1上方
        path.moveTo(pos1.x()+width1/2, pos1.y()-LINE_AND_PIC_SPACE);
        path.lineTo(pos2.x()+width1/2, pos2.y()+height2+LINE_AND_PIC_SPACE);
    }
    else
    {//点2在点1下方
        path.moveTo(pos1.x()+width1/2, pos1.y()+height1+LINE_AND_PIC_SPACE);
        path.lineTo(pos2.x()+width1/2, pos2.y()-LINE_AND_PIC_SPACE);
    }
}

void CArrowPathItem::getPathForSameY(const QPointF &pos1, int width1, int height1, const QPointF &pos2, int width2, int height2, QPainterPath &path)
{
    if( pos1.x() > pos2.x() )
    {//点2在点1左侧
        path.moveTo(pos1.x()-LINE_AND_PIC_SPACE, pos1.y()+height1/2);
        path.lineTo(pos2.x()+width2+LINE_AND_PIC_SPACE, pos1.y()+height1/2);
    }
    else
    {//点2在点1右侧
        path.moveTo(pos1.x()+width1+LINE_AND_PIC_SPACE, pos1.y()+height1/2);
        path.lineTo(pos2.x()-LINE_AND_PIC_SPACE, pos1.y()+height1/2);
    }
}

void CArrowPathItem::getPathForOther(const QPointF &pos1, int width1, int height1, const QPointF &pos2, int width2, int height2, QPainterPath &path)
{
    if( pos1.y() > pos2.y() )
    {//点2在点1的上方
        path.moveTo(pos1.x()+width1/2, pos1.y()-LINE_AND_PIC_SPACE);
        path.lineTo(pos1.x()+width1/2, pos1.y()-(pos1.y()-pos2.y()-height2-LINE_AND_PIC_SPACE)/2);
        path.lineTo(pos2.x()+width2/2, pos1.y()-(pos1.y()-pos2.y()-height2-LINE_AND_PIC_SPACE)/2);
        path.lineTo(pos2.x()+width2/2, pos2.y()+height1+LINE_AND_PIC_SPACE);
    }
    else if( pos1.y() < pos2.y() )
    {//点2在点1的下方
        path.moveTo(pos1.x()+width1/2, pos1.y()+height1+LINE_AND_PIC_SPACE);
        path.lineTo(pos1.x()+width1/2, pos1.y()+height1+(pos2.y()-pos1.y()-height1-LINE_AND_PIC_SPACE)/2);
        path.lineTo(pos2.x()+width1/2, pos1.y()+height1+(pos2.y()-pos1.y()-height1-LINE_AND_PIC_SPACE)/2);
        path.lineTo(pos2.x()+width1/2, pos2.y()-LINE_AND_PIC_SPACE);
    }
}

bool CArrowPathItem::getItemInfo(const QGraphicsItem *item, int &width, int &height)
{
    if( !item ) return false;

    if( ITEM_TYPE_PIXMAPITEM == item->type() )
    {   //QGraphicsPixmapItem类型：7
        QGraphicsPixmapItem *itemTmp = (QGraphicsPixmapItem*)item;
        width = itemTmp->pixmap().width();
        height = itemTmp->pixmap().height();
    }

    return true;
}

bool CArrowPathItem::getArrow(const QPainterPath &path, QPolygonF &arrow)
{
    int elementCount = path.elementCount();
    if( elementCount < 2 ) return false;

    qreal arrowsize = 10;
    QPainterPath::Element ele1 = path.elementAt(elementCount-2);
    QPainterPath::Element ele2 = path.elementAt(elementCount-1);

    double angle = std::atan2(-(ele1.y-ele2.y)
                              , ele1.x-ele2.x); //反正切 [-PI,PI]，目前未做斜线的情况，故斜率为0
    QPointF pointf(ele2);

    QPointF arrowP1 = pointf +
            QPointF(sin(angle + m_pi / 3) * arrowsize, //计算对边
                    cos(angle + m_pi / 3) * arrowsize); //计算临边

    QPointF arrowP2 = pointf +
            QPointF(sin(angle + m_pi - m_pi / 3) * arrowsize,
                    cos(angle + m_pi - m_pi / 3) * arrowsize);

    arrow.clear();
    arrow << pointf << arrowP1 << arrowP2;

    return true;
}

void CArrowPathItem::setLineColor(const QColor &color)
{
    m_penColor = color;
}

void CArrowPathItem::setLinePen(const QPen &pen)
{
    m_pen = pen;
}

void CArrowPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( m_pStartItem->collidesWithItem(m_pendItem) ) return;

    m_pen.setColor(m_penColor);

    painter->setPen(m_pen);
    painter->setBrush(m_pen.color());

    int startWidth = 0;
    int startHeight = 0;
    int endWidth = 0;
    int endHeight = 0;

    getItemInfo(m_pStartItem, startWidth, startHeight);
    getItemInfo(m_pendItem, endWidth, endHeight);
    getPath(m_pStartItem->pos(), startWidth, startHeight, m_pendItem->pos(), endWidth, endHeight, m_path);

    m_pathItem->setPen(m_pen);
    m_pathItem->setPath(m_path);
    if( m_isDrawArrow )
    {
        getArrow(m_path, m_arrowHead);
        m_ploygonItem->setBrush(m_penColor);
        m_ploygonItem->setPolygon(m_arrowHead);
    }
}
