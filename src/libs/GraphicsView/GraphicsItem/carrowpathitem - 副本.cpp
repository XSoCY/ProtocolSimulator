#include "carrowpathitem.h"
#include <QDebug>

CArrowPathItem::CArrowPathItem(QGraphicsItem *startI, QGraphicsItem *endI, QGraphicsItem *parent):
    QGraphicsLineItem (parent)
{
    m_pi = 3.14;
    m_pendItem = endI; //起点item
    m_pStartItem = startI; //终点item
    this->setZValue(m_pStartItem->zValue() - 1); //目的：让箭头后置
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF CArrowPathItem::boundingRect() const
{
    //item绘制区域的估计值
    qreal extra = (this->pen().width() + 20) /2;
    return QRectF(line().p1(),QSizeF(line().p2().x()-line().p1().x(),line().p2().y() - line().p1().y()))
            .normalized().adjusted(-extra,-extra,extra,extra);
}

void CArrowPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( m_pStartItem->collidesWithItem(m_pendItem) ) return;

    QPen pen(Qt::black);
    painter->setPen(pen);

    painter->setBrush(Qt::black);
    qreal arrowsize = 10;

    QLineF centerLine(m_pStartItem->pos(),m_pendItem->pos());
    QPolygonF endPolygon = m_pendItem->polygon();//获取item的点组合（闭环路）
    QPointF p1 = endPolygon.first() + m_pendItem->pos();//item的左上方点  + item在场景的位置点（偏移得到左上点在场景中的位置）
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for(int i = 1;i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i) + m_pendItem->pos();//偏移得到场景中的位置点
        polyLine = QLineF(p1,p2);//两点构成直线

        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine,&intersectPoint);//两条线比较是否有交集   存在
        if(intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    painter->setPen(Qt::black);
    setLine(QLineF(intersectPoint,m_pStartItem->pos()));

    double angle = std::atan2(-line().dy(),line().dx()); //反正切 [-PI,PI]
    QPointF arrowP1 = line().p1() +
            QPointF(sin(angle + m_pi / 3) * arrowsize, //计算对边
                    cos(angle + m_pi / 3) * arrowsize); //计算临边
    QPointF arrowP2 = line().p1() +
            QPointF(sin(angle + m_pi - m_pi / 3) * arrowsize,
                    cos(angle + m_pi - m_pi / 3) * arrowsize);

    arrowHead.clear();
    arrowHead<<line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

}

QPainterPath CArrowPathItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}
