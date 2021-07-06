#include "labeldraw.h"
#include <QPainter>

LabelDraw::LabelDraw(QWidget *parent) : QLabel(parent)
{
}

void LabelDraw::SetColorAndSize(QColor color, uint uiX, uint uiY, uint uiSize)
{
    m_Color = color;
    m_uiSize = uiSize;
    m_uiX = uiX;
    m_uiY = uiY;
}

void LabelDraw::paintEvent(QPaintEvent * paint)
{
    QPainter Painter(this);
    Painter.setPen(m_Color);
    Painter.setBrush(m_Color);
    Painter.drawEllipse(m_uiX, m_uiY,m_uiSize,m_uiSize);
}

