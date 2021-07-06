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

enum QGraphicsItemType
{
    ITEM_TYPE_PIXMAPITEM = 7,       //QGraphicsPixmapItem
};

class GRAPHICSVIEWSHARED_EXPORT CArrowPathItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 4 };

    //构造函数(两个item参数)
    CArrowPathItem(QGraphicsItem *startI, QGraphicsItem *endI, bool isDrawArrow = true, QGraphicsItem *parent = nullptr);

    /**
     * @brief setLineColor  设置线颜色
     * @param color  颜色
     * @return 无
     */
    void setLineColor(const QColor &color);

    /**
     * @brief setLinePen  设置线风格
     * @param pen  风格参数
     * @return 无
     */
    void setLinePen(const QPen &pen);

    QRectF boundingRect() const { return QRectF();}

protected:
    /**
     * @brief paint   实际绘制
     * @param textRows  文本行数
     * @return QRectF
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief getPath 获取两点路径（获取路径调用此函数即可）
     * @param pos1 点1的左上角位置坐标
     * @param width1 点1元素的宽度
     * @param height1 点1元素的高度
     * @param pos2 点2左上角位置坐标
     * @param width2 点2元素的宽度
     * @param height2 点2元素的高度
     * @param path 输出参数，获取到的路径点集合
     * @return 无
     */
    void getPath(const QPointF &pos1, int width1, int height1
                 , const QPointF &pos2, int width2, int height2
                 , QPainterPath &path);

    /**
     * @brief getPath 获取在同一垂直线上的两点的路径
     * @param pos1 点1的左上角位置坐标
     * @param width1 点1元素的宽度
     * @param height1 点1元素的高度
     * @param pos2 点2左上角位置坐标
     * @param width2 点2元素的宽度
     * @param height2 点2元素的高度
     * @param path 输出参数，获取到的路径点集合
     * @return 无
     */
    void getPathForSameX(const QPointF &pos1, int width1, int height1
                         , const QPointF &pos2, int width2, int height2
                         , QPainterPath &path);

    /**
     * @brief getPath 获取在同一水平线上的两点的路径
     * @param pos1 点1的左上角位置坐标
     * @param width1 点1元素的宽度
     * @param height1 点1元素的高度
     * @param pos2 点2左上角位置坐标
     * @param width2 点2元素的宽度
     * @param height2 点2元素的高度
     * @param path 输出参数，获取到的路径点集合
     * @return 无
     */
    void getPathForSameY(const QPointF &pos1, int width1, int height1
                         , const QPointF &pos2, int width2, int height2
                         , QPainterPath &path);

    /**
     * @brief getPath 获取不在同一水平线上也不在同一垂直线上的两点的路径
     * @param pos1 点1的左上角位置坐标
     * @param width1 点1元素的宽度
     * @param height1 点1元素的高度
     * @param pos2 点2左上角位置坐标
     * @param width2 点2元素的宽度
     * @param height2 点2元素的高度
     * @param path 输出参数，获取到的路径点集合
     * @return 无
     */
    void getPathForOther(const QPointF &pos1, int width1, int height1
                         , const QPointF &pos2, int width2, int height2
                         , QPainterPath &path);

    /**
     * @brief getItemInfo 获取元素的高度和宽度
     * @param item 元素对象
     * @param width 输出参数：宽度
     * @param height 输出参数：高度
     * @return 无
     */
    bool getItemInfo(const QGraphicsItem *item, int &width, int &height);

    /**
     * @brief getItemInfo 根据路径信息，获取箭头图形
     * @param path 路径
     * @param QPolygonF 图形
     * @return true-成功；false-失败
     */
    bool getArrow(const QPainterPath &path, QPolygonF &arrow);
private:
    QGraphicsItem               *m_pStartItem;      //起始点
    QGraphicsItem               *m_pendItem;        //终点
    QGraphicsPathItem           *m_pathItem;        //路径
    QGraphicsPolygonItem        *m_ploygonItem;     //箭头
    QPolygonF                   m_arrowHead;        //箭头形状
    QPainterPath                m_path;             //路径节点
    QColor                      m_penColor;         //线颜色
    QPen                        m_pen;              //线画笔
    bool                        m_isDrawArrow;      //是否画箭头

    double                      m_pi;               //π值
};

#endif // CARROWLINEITEM_H
