#ifndef ICONDITONPRODUCT_H
#define ICONDITONPRODUCT_H

#include <QVariant>

class IConditonProduct
{
public:
    IConditonProduct() {}
    virtual ~IConditonProduct() {}

    virtual bool judge(const QVariant& value) const = 0;
};

#endif // ICONDITONPRODUCT_H
