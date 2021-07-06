#include "graphicsview.h"

GraphicsView *GraphicsView::m_instance = NULL;

GraphicsView::GraphicsView()
{
    m_httpPathBase = "http://192.168.31.2:9002/";
}
