#ifndef INTEGEREQUALPRODUCT_H
#define INTEGEREQUALPRODUCT_H

#include "iconditonproduct.h"
#include <QDomElement>

class IntegerEqualProduct : public IConditonProduct
{
public:
    IntegerEqualProduct(const QDomElement& doc_element);

    virtual bool judge(const QVariant& value) const;

private:
    quint64 compare_value_ = 0;
};

#endif // INTEGEREQUALPRODUCT_H
