#ifndef PROPERTYACTION_H
#define PROPERTYACTION_H

#include "iactionproduct.h"
#include <QDomElement>
#include <QVariant>

class PropertyAction : public IActionProduct
{
public:
    PropertyAction(const QDomElement &doc_element);

    virtual void excute(const QMap<QString, QWidget *> &param_id_to_widget) const;

private:
    QString param_id_;
    QString property_name_;
    QVariant value_    = 0;
    QVariant strvalue_ = 0;
};

#endif  // PROPERTYACTION_H
