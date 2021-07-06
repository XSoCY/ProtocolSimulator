#include "integerequalproduct.h"
#include <QVariant>
#include <QDebug>

IntegerEqualProduct::IntegerEqualProduct(const QDomElement &doc_element)
{
    compare_value_ = doc_element.attribute("value").toULongLong();
}

bool IntegerEqualProduct::judge(const QVariant &value) const
{
//    qDebug() << value.toULongLong() << compare_value_ << (value.toULongLong() == compare_value_);
    return (value.toULongLong() == compare_value_);
}
