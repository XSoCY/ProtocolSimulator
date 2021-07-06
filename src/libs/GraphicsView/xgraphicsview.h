/*
 * 说明：view类，集成qgraphicsview，对界面上显示的元素进行统一管理，
 * 通过name进行增、删、改、查等
 * 创建者：xuejh
 * 创建日期：2020-12-24
 */
#ifndef XGRAPHICSVIEW_H
#define XGRAPHICSVIEW_H

#include "carrowpathitem.h"
#include "cpixmaptextitem.h"
#include "xgraphicsscene.h"
#include "graphicsview_global.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QMap>

class GRAPHICSVIEWSHARED_EXPORT XGraphicsView : public QGraphicsView
{
public:
    XGraphicsView();

    /**
     * @brief addPixmapTextItem  添加图片节点
     * @param name  节点名称
     * @param item  节点对象
     * @return 无
     */
    void addPixmapTextItem(const QString &name, CPixmapTextItem *item);

    /**
     * @brief getPixmapTextItem  获取图片节点
     * @param name  节点名称
     * @return 成功-节点对象；失败-NULL
     */
    CPixmapTextItem *getPixmapTextItem(const QString &name);

    /**
     * @brief addArrowPathItem  添加连接线
     * @param name  节点名称
     * @param item  连接线对象
     * @return 无
     */
    void addArrowPathItem(const QString &name, CArrowPathItem *item);

    /**
     * @brief getArrowPathItem  获取连接线对象
     * @param name  节点名称
     * @return 成功-连接线对象；失败-NULL
     */
    CArrowPathItem *getArrowPathItem(const QString &name);

    /**
     * @brief removePixmapTextItem  移除节点对象
     * @param name  节点名称
     * @return 无
     */
    void removePixmapTextItem(const QString &name);

    /**
     * @brief removeArrowPathItem  移除连接线
     * @param name  节点名称
     * @return 无
     */
    void removeArrowPathItem(const QString &name);

protected:
    /**
     * @brief wheelEvent  鼠标滚动事件，用于放大缩小scene
     * @param event  事件对象
     * @return 无
     */
    void wheelEvent(QWheelEvent *event);

private:
    QMap<QString, CPixmapTextItem*>         m_mapPixmapTextItems;   //保存所有的节点对象
    QMap<QString, CArrowPathItem*>          m_mapArrowPathItems;    //保存所有的连接线

    XGraphicsScene                          *m_scene;
    double                                  m_scale;
};

#endif // XGRAPHICSSCENE_H
