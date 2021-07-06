#include "specialnagativedoublespinbox.h"

SpecialNagativeDoubleSpinbox::SpecialNagativeDoubleSpinbox(const QDomElement& doc_element, QWidget* parent)
    : QDoubleSpinBox(parent)
{
    coefficient_  = doc_element.attribute("coefficient").toDouble();
    nagetive_bit_ = doc_element.attribute("nagetiveBit").toInt();
    auto decimal  = doc_element.attribute("decimal").toInt();
    auto min      = doc_element.attribute("min").toDouble();
    auto max      = doc_element.attribute("max").toDouble();

    setDecimals(decimal);
    setRange(min, max);
}

QVariant SpecialNagativeDoubleSpinbox::paramVaule() const
{
    auto      double_value = value();
    qlonglong int_value    = qRound64(double_value / coefficient_);

    if (int_value < 0) {
        int_value = -int_value;
        int_value = (~((1 << nagetive_bit_) - 1)) | int_value;
    }

    return QVariant(int_value);
}

void SpecialNagativeDoubleSpinbox::setParamVaule(const QVariant& param_vaule)
{
    if (param_vaule.canConvert<qlonglong>()) {
        qlonglong int_value = param_vaule.toLongLong();
        if (int_value < 0) {
            int_value = ((1 << (nagetive_bit_ - 1)) - 1) & int_value;
            int_value = -int_value;
        }
        double double_value = int_value * coefficient_;
        setValue(double_value);
    }
}
