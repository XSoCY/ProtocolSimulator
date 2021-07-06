/*
 * 在graphicsview上显示带箭头的线item：根据两个graphicsitem
 * 创建者：xuejh
 * 创建日期：2020-12-24
 */
#ifndef CARROWLINEITEM_H
#define CARROWLINEITEM_H

#include "graphicsview_global.h"
#include <QGraphicsObject>
#include <QPainter>

class GRAPHICSVIEWSHARED_EXPORT CArrowPathItem : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 4 };

    //构造函数(两个item参数)
    CArrowPathItem(QGraphicsItem *startI, QGraphicsItem *endI, QGraphicsItem *parent = nullptr);

    /**
     * @brief boundingRect   item绘制区域的估计值
     * @param textRows  文本行数
     * @return QRectF
     */
    QRectF boundingRect() const override;

    /**
     * @brief paint   实际绘制
     * @param textRows  文本行数
     * @return QRectF
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override;

    int type() const override { return Type; }

    QPainterPath shape() const override;

private:
    QGraphicsItem *m_pStartItem;
    QGraphicsItem *m_pendItem;
    QPolygonF arrowHead;

    double m_pi;
};

#endif // CARROWLINEITEM_H
