/*
 * 在graphicsview上显示图片的同时显示文字item
 * 创建者：xuejh
 * 创建日期：2020-12-24
 */
#ifndef CTEXTITEM_H
#define CTEXTITEM_H

#include "graphicsview_global.h"

#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class GRAPHICSVIEWSHARED_EXPORT CPixmapTextItem : public QGraphicsPixmapItem
{
public:
    CPixmapTextItem();
    CPixmapTextItem(QPixmap pixmap, QPixmap pixmapFault, QString text);

public:
    /**
     * @brief setPix   设置显示图片
     * @param pixmap  图片
     * @param width   宽度
     * @param height  高度
     * @return
     */
    void setPix(const QPixmap &pixmap, int width = 0, int height = 0);

    /**
     * @brief setPix   设置图片宽度和高度
     * @param width   宽度
     * @param height  高度
     * @return
     */
    void setPixSize(int width, int height);

    /**
     * @brief setText 设置显示的文字
     * @param text 文字
     * @return
     */
    void setText(const QString &text);

    /**
     * @brief text 获取显示的文字
     * @return 文字
     */
    QString text();

    /**
     * @brief setFont 设置文字的字体
     * @param font 文字字体
     * @return
     */
    void setFont(const QFont &font);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    int                 m_pixmapWidth;          //元素宽度
    int                 m_pixmapHeight;         //元素高度
    QPixmap             m_normalPixmap;         //正常显示图片
    QPixmap             m_faultPixmap;          //故障显示图片

    QString             m_text;                 //显示文字
    QGraphicsTextItem   *m_textItem;            //显示文字的item

    QFont               m_font;                 //字体设置
};

#endif // CTEXTITEM_H
