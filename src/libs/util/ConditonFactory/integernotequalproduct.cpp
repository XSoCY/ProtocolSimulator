#include "integernotequalproduct.h"
#include <QVariant>
#include <QDebug>

IntegerNotEqualProduct::IntegerNotEqualProduct(const QDomElement &doc_element)
{
    compare_value_ = doc_element.attribute("value").toULongLong();
}

bool IntegerNotEqualProduct::judge(const QVariant &value) const
{
//    qDebug() << value.toULongLong() << compare_value_ << (value.toULongLong() != compare_value_);
    return (value.toULongLong() != compare_value_);
}
