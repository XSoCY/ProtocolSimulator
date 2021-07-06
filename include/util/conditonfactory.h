#ifndef CONDITONFACTORY_H
#define CONDITONFACTORY_H

#include <QDomElement>
#include "iconditonproduct.h"

class ConditonFactory
{
public:
    static ConditonFactory& instance();

    IConditonProduct* createProduct(const QString& type, const QDomElement& doc_element);

protected:
    ConditonFactory();
};

#endif // CONDITONFACTORY_H
