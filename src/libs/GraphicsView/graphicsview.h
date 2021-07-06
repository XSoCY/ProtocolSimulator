#ifndef HTTPRESPONSEMANAGER_H
#define HTTPRESPONSEMANAGER_H

#include "graphicsview_global.h"
#include <QObject>

class GRAPHICSVIEWSHARED_EXPORT GraphicsView
{

public:
    static GraphicsView *getInstance()
    {
        if( !m_instance ) m_instance = new GraphicsView;

        return m_instance;
    }

private:
    GraphicsView();

    static GraphicsView *m_instance;

    QString m_httpPathBase;
};

#endif // HTTPRESPONSEMANAGER_H
