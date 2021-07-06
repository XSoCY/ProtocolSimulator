#ifndef INTEGERNOTEQUALPRODUCT_H
#define INTEGERNOTEQUALPRODUCT_H

#include "iconditonproduct.h"
#include <QDomElement>

class IntegerNotEqualProduct : public IConditonProduct
{
public:
    IntegerNotEqualProduct(const QDomElement& doc_element);

    virtual bool judge(const QVariant& value) const;

private:
    quint64 compare_value_ = 0;
};

#endif // INTEGERNOTEQUALPRODUCT_H
