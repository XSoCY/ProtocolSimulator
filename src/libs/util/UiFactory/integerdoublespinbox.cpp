#include "integerdoublespinbox.h"
#include <QDebug>

IntegerDoubleSpinBox::IntegerDoubleSpinBox(const QDomElement& doc_element, QWidget* parent) : QDoubleSpinBox(parent)
{
    coefficient_ = doc_element.attribute("coefficient").toDouble();
    auto decimal = doc_element.attribute("decimal").toInt();
    auto min     = doc_element.attribute("min").toDouble();
    auto max     = doc_element.attribute("max").toDouble();

    setDecimals(decimal);
    setRange(min, max);
}

QVariant IntegerDoubleSpinBox::paramVaule() const
{
    auto      double_value = value();
    qlonglong int_value    = qRound64(double_value / coefficient_);
    return QVariant(int_value);
}

void IntegerDoubleSpinBox::setParamVaule(const QVariant& param_vaule)
{
    if (param_vaule.canConvert<qlonglong>()) {
        qlonglong int_value    = param_vaule.toLongLong();
        double    double_value = int_value * coefficient_;
        setValue(double_value);
    }
}
