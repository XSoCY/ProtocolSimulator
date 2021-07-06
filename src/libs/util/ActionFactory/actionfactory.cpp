#include "actionfactory.h"
#include "propertyaction.h"

ActionFactory &ActionFactory::instance()
{
    static ActionFactory instance;
    return instance;
}

IActionProduct *ActionFactory::createProduct(const QString &type, const QDomElement &doc_element)
{
    if (type == "property") {
        return new PropertyAction(doc_element);
    } else {
        return nullptr;
    }
}

ActionFactory::ActionFactory() {}
