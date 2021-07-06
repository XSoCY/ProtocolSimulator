#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include <QDomElement>
#include "iactionproduct.h"

class ActionFactory
{
public:
    static ActionFactory& instance();

    IActionProduct* createProduct(const QString& type, const QDomElement& doc_element);

protected:
    ActionFactory();
};

#endif // ACTIONFACTORY_H
