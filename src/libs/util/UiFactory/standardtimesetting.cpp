#include "standardtimesetting.h"

StandardTimeSetting::StandardTimeSetting(const QDomElement& doc_element, QWidget* parent):QTimeEdit(parent)
{
   coefficient_=doc_element.attribute("coefficient").toDouble();
   setDisplayFormat("hh:mm:ss.zzz");
}

QVariant StandardTimeSetting::paramVaule() const
{
    return QVariant(time().msecsSinceStartOfDay()/coefficient_);
}

void StandardTimeSetting::setParamVaule(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<quint32>())
    {
        quint32 int_value    = param_vaule.toUInt();
        double    double_value = int_value * coefficient_;
        setTime(QTime::fromMSecsSinceStartOfDay(static_cast<int>(double_value)));
    }
}

