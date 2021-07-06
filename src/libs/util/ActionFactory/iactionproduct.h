#ifndef IACTIONPRODUCT_H
#define IACTIONPRODUCT_H

#include <QMap>

class QWidget;

class IActionProduct
{
public:
    IActionProduct() {}
    virtual ~IActionProduct() {}

    virtual void excute(const QMap<QString, QWidget*>& param_id_to_widget) const = 0;
};

#endif // IACTIONPRODUCT_H
