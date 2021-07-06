#ifndef XGRAPHICSSCENE_H
#define XGRAPHICSSCENE_H

#include "carrowpathitem.h"
#include "cpixmaptextitem.h"
#include "xgraphicswidget.h"
#include "graphicsview_global.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QMap>

class GRAPHICSVIEWSHARED_EXPORT XGraphicsWidget : public QGraphicsView
{
public:
    XGraphicsWidget();

    void addPixmapTextItem(const QString &name, CPixmapTextItem *item);
    CPixmapTextItem *getPixmapTextItem(const QString &name);

    void addArrowPathItem(const QString &name, CArrowPathItem *item);
    CArrowPathItem *getArrowPathItem(const QString &name);

    void removePixmapTextItem(const QString &name);
    void removeArrowPathItem(const QString &name);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    QMap<QString, CPixmapTextItem*>         m_mapPixmapTextItems;
    QMap<QString, CArrowPathItem*>          m_mapArrowPathItems;

    QGraphicsScene                          *m_scene;
    double                                  m_scale;
};

#endif // XGRAPHICSSCENE_H
