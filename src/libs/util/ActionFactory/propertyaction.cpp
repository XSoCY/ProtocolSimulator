#include "propertyaction.h"
#include <QDebug>
#include <QWidget>

PropertyAction::PropertyAction(const QDomElement &doc_element)
{
    param_id_      = doc_element.attribute("paramID");
    property_name_ = doc_element.attribute("propertyName");
    if (doc_element.hasAttribute("strvalue")) {
        auto str_value = doc_element.attribute("strvalue");
        value_         = str_value;
    }
    else {
        auto str_value = doc_element.attribute("value");
        if (str_value.startsWith("0x", Qt::CaseInsensitive)) {
            value_ = str_value.toULongLong(nullptr, 16);
        }
        else {
            value_ = str_value.toULongLong();
        }
    }
}

void PropertyAction::excute(const QMap<QString, QWidget *> &param_id_to_widget) const
{
    if (param_id_to_widget.contains(param_id_)) {
        if (auto widget = param_id_to_widget.value(param_id_)) {
            //            qDebug() << "excute" << param_id_ << property_name_ << value_;
            widget->setProperty(property_name_.toStdString().c_str(), value_);
        }
    }
}
