#ifndef LABELDRAW_H
#define LABELDRAW_H

#include <QWidget>
#include <QLabel>
#include <QColor>
#include "util_global.h"

class UTILSHARED_SELF_EXPORT LabelDraw : public QLabel
{
    Q_OBJECT
public:
    explicit LabelDraw(QWidget *parent = nullptr);
    void SetColorAndSize(QColor color, uint uiX, uint uiY, uint uiSize);

    void paintEvent(QPaintEvent * paint);
signals:

public slots:

private:
    QColor m_Color;
    uint m_uiSize;
    uint m_uiX;
    uint m_uiY;
};

#endif // LABELDRAW_H
