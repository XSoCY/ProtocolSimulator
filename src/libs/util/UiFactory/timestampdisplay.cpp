#include "timestampdisplay.h"
#include <QTime>

TimeStampDisplay::TimeStampDisplay(const QDomElement &doc_element, QWidget *parent) : QLabel(parent)
{
    coefficient_ = doc_element.attribute("coefficient").toDouble();
}

QVariant TimeStampDisplay::paramVaule() const
{
    return QVariant();
}

void TimeStampDisplay::setParamVaule(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<qlonglong>()) {
        qlonglong int_value    = param_vaule.toLongLong();
        double    double_value = int_value * coefficient_;

        auto time = QTime::fromMSecsSinceStartOfDay(static_cast<int>(double_value));

        auto decimal = int_value % (qRound(1.0 / coefficient_));
        setText(QString("%1.%2").arg(time.toString("hh:mm:ss.zzz")).arg(decimal));
    }
}
