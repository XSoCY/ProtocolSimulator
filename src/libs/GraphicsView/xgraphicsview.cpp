#include "xgraphicsview.h"
#include <QDebug>

XGraphicsView::XGraphicsView()
    : m_scene(NULL)
    , m_scale(1)
{
    m_scene = new XGraphicsScene;
    this->setScene(m_scene);
}

void XGraphicsView::addPixmapTextItem(const QString &name, CPixmapTextItem *item)
{
    if ( !item ) return;

    CPixmapTextItem *itemTmp = getPixmapTextItem(name);
    if( itemTmp ) m_scene->removeItem(itemTmp);

    m_mapPixmapTextItems.insert(name, item);
    if( m_scene ) m_scene->addItem(item);
}

CPixmapTextItem *XGraphicsView::getPixmapTextItem(const QString &name)
{
    CPixmapTextItem *item = NULL;
    QMap<QString, CPixmapTextItem*>::iterator iter;
    for(iter=m_mapPixmapTextItems.begin(); iter!=m_mapPixmapTextItems.end(); ++iter)
    {
        if( iter.key() == name )
        {
            item = iter.value();
            break;
        }
    }

    return item;
}

void XGraphicsView::addArrowPathItem(const QString &name, CArrowPathItem *item)
{
    if( !item ) return ;

    CArrowPathItem *itemTmp = getArrowPathItem(name);
    if( itemTmp ) m_scene->removeItem(itemTmp);

    m_mapArrowPathItems.insert(name, item);
    if( m_scene ) m_scene->addItem(item);
}

CArrowPathItem *XGraphicsView::getArrowPathItem(const QString &name)
{
    CArrowPathItem *item = NULL;
    QMap<QString, CArrowPathItem*>::iterator iter;
    for(iter=m_mapArrowPathItems.begin(); iter!=m_mapArrowPathItems.end(); ++iter)
    {
        if( iter.key() == name )
        {
            item = iter.value();
            break;
        }
    }

    return item;
}

void XGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal scaleValue = 0.2;

    //判断是否按下ctrl键
    if( QApplication::keyboardModifiers() != Qt::ControlModifier )
    {
        //未按下ctrl键
        QGraphicsView::wheelEvent(event);
        return;
    }

    if(event->delta() > 0)
    {// 放大
        if(m_scale < 2){
            m_scale *= (1 + scaleValue);
            this->scale(1 + scaleValue, 1 + scaleValue);
        }
        else m_scale = 2;
    }
    else
    {// 缩小
        if(m_scale > 0.2){
            m_scale *= (1 - scaleValue);
            this->scale(1 - scaleValue, 1 - scaleValue);
        }
        else m_scale = 0.2;
    }
}
