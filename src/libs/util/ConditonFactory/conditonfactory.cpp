#include "conditonfactory.h"
#include "integerequalproduct.h"
#include "integernotequalproduct.h"

ConditonFactory &ConditonFactory::instance()
{
    static ConditonFactory instance;
    return instance;
}

IConditonProduct *ConditonFactory::createProduct(const QString &type, const QDomElement &doc_element)
{
    if (type == "=="){
        return new IntegerEqualProduct(doc_element);
    } else if (type == "!=") {
        return new IntegerNotEqualProduct(doc_element);
    }
    return nullptr;
}

ConditonFactory::ConditonFactory() {}
