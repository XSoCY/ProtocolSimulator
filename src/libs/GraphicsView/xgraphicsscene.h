/*
 * scene,为处理一些特使事件而写，如鼠标等需要特殊处理时，在此编写
 * 创建者：xuejh
 * 创建日期：2021-01-05
 */
#ifndef XGRAPHICSSCENE_H
#define XGRAPHICSSCENE_H

#include "graphicsview_global.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>

class GRAPHICSVIEWSHARED_EXPORT XGraphicsScene : public QGraphicsScene
{
public:
    XGraphicsScene();

};

#endif // XGRAPHICSSCENE_H
