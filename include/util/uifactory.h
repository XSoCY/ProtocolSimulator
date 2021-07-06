#ifndef UIFACTORY_H
#define UIFACTORY_H

#include <QDomElement>
#include <QVariant>
#include "util_global.h"
class QWidget;

class UTILSHARED_SELF_EXPORT UiFactory
{
public:
    static UiFactory& instance();

    QWidget* createProduct(const QString& type, const QDomElement& ui_xml, const QDomElement& relation_xml = QDomElement());

protected:
    UiFactory();
};

#endif  // UIFACTORY_H
