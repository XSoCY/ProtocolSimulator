#include "AutoFixedWidthListWidget.h"
#include <QFontMetrics>

AutoFixedWidthListWidget::AutoFixedWidthListWidget(QWidget* parent) : QListWidget(parent), m_fixedItemHeight(60)
{
    setFocusPolicy(Qt::NoFocus);
}

void AutoFixedWidthListWidget::fixedWidthToMaxTextWidth()
{
    int maxWidth = 0;
    const int rc = count();
    for (int i = 0; i < rc; i++)
    {
        QListWidgetItem* it = item(i);
        it->setSizeHint(QSize(0, fixedItemHeight()));

        QFontMetrics fontM(font());
        // qDebug() << "=>" << font().pixelSize() << " " <<  font().pointSize();
        const QRect fontRect = fontM.boundingRect(it->text());

        if (fontRect.width() > maxWidth)
        {
            maxWidth = fontRect.width();
        }
    }

    if (maxWidth > 0)
    {
        setFixedWidth(maxWidth + 100);
    }
}

int AutoFixedWidthListWidget::fixedItemHeight() const
{
    return m_fixedItemHeight;
}

void AutoFixedWidthListWidget::setFixedItemHeight(int fixedItemHeight)
{
    m_fixedItemHeight = fixedItemHeight;
    update();
}

void AutoFixedWidthListWidget::mouseMoveEvent(QMouseEvent* e)
{
    QListWidget::mouseMoveEvent(e);
}
