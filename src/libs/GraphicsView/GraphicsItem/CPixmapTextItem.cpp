#include "cpixmaptextitem.h"
#include <QTextItem>
#include <QGraphicsScene>
#include <QDebug>

CPixmapTextItem::CPixmapTextItem()
{

}

CPixmapTextItem::CPixmapTextItem(QPixmap pixmap, QPixmap pixmapFault, QString text)
    : QGraphicsPixmapItem(pixmap)
    , m_textItem(NULL)
    , m_pixmapHeight(0)
    , m_pixmapWidth(0)
    , m_faultPixmap(pixmapFault)
    , m_normalPixmap(pixmap)
{
    m_text = text;
}

void CPixmapTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPointF pointf = this->pos();
    int pixWidth = pixmap().width();
    int pixHeight = pixmap().height();

    qDebug() << "CPixmapTextItem::paint";

    //计算文字需要的宽度
    painter->setFont(m_font);
    QFontMetrics fm = painter->fontMetrics();
    int textWidth = fm.width(m_text);

    //计算文字起始点
    int x = pointf.x() + (pixWidth - textWidth)/2;
    int y = pointf.y() + pixHeight + 10;

    if( !m_textItem )
    {//创建QGraphicsTextItem
        m_textItem = new QGraphicsTextItem(m_text);

        //设置字体和pos点
        m_textItem->setFont(m_font);
        m_textItem->setPos(x, y);

        //把item加入到QGraphicsScene中去
        QGraphicsScene *scene = this->scene();
        if( scene ) scene->addItem(m_textItem);
    }

    QGraphicsPixmapItem::paint(painter, option, widget);
}

void CPixmapTextItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "CPixmapTextItem::dragEnterEvent";
}
void CPixmapTextItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "CPixmapTextItem::dragLeaveEvent";
}
void CPixmapTextItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "CPixmapTextItem::dragMoveEvent";
}
void CPixmapTextItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "CPixmapTextItem::dropEvent";
}
void CPixmapTextItem::focusInEvent(QFocusEvent *event)
{
    qDebug() << "CPixmapTextItem::focusInEvent";
}
void CPixmapTextItem::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "CPixmapTextItem::focusOutEvent";
}
void CPixmapTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "CPixmapTextItem::hoverEnterEvent";
}
void CPixmapTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "CPixmapTextItem::hoverMoveEvent";
}
void CPixmapTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "CPixmapTextItem::hoverLeaveEvent";
}

void CPixmapTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CPixmapTextItem::mouseMoveEvent";
}

void CPixmapTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CPixmapTextItem::mouseReleaseEvent";
}

void CPixmapTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "CPixmapTextItem::mouseDoubleClickEvent";
}

void CPixmapTextItem::setPix(const QPixmap &pixmap, int width, int height)
{
    m_pixmapWidth = width;
    m_pixmapHeight = height;

    if( 0 != width || 0 != height ) this->setPixmap(pixmap.scaled(width, height));
    else this->setPixmap(pixmap);
}

void CPixmapTextItem::setPixSize(int width, int height)
{
    m_pixmapWidth = width;
    m_pixmapHeight = height;

    QPixmap pixmap = this->pixmap().scaled(width, height);
    this->setPixmap(pixmap);
}

void CPixmapTextItem::setText(const QString &text)
{
    m_text = text;

    if( m_textItem ) m_textItem->setPlainText(m_text);
}

QString CPixmapTextItem::text()
{
    return m_text;
}

void CPixmapTextItem::setFont(const QFont &font)
{
    m_font = font;
    if( m_textItem ) m_textItem->setFont(m_font);
}
