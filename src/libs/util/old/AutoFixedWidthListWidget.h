#ifndef AutoFixedWidthListWidget_H
#define AutoFixedWidthListWidget_H

#include "util_global.h"

#include <QListWidget>

class UTILSHARED_EXPORT AutoFixedWidthListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AutoFixedWidthListWidget(QWidget* parent = nullptr);

public:
    void fixedWidthToMaxTextWidth();

public:
    int fixedItemHeight() const;
    void setFixedItemHeight(int fixedItemHeight);

protected:
    void mouseMoveEvent(QMouseEvent* e);

private:
    int m_fixedItemHeight;
};

#endif  // AutoFixedWidthListWidget_H
