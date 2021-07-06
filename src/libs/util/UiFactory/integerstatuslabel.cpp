#include "integerstatuslabel.h"
#include <QDebug>
#include <QPainter>

IntegerStatusLabel::IntegerStatusLabel(const QDomElement& doc_element, QWidget* parent) : StatusLabel(parent)
{
    normal_value_   = doc_element.attribute("normalValue", "1").toULongLong();
    abnormal_value_ = doc_element.attribute("abnormalValue", "2").toULongLong();
}

QVariant IntegerStatusLabel::paramVaule() const
{
    return 0;
}

void IntegerStatusLabel::setParamVaule(const QVariant& param_vaule)
{
    if (param_vaule.canConvert<int>()) {
        auto int_value = param_vaule.toULongLong();
        if (int_value == abnormal_value_) {
            //异常
            setStatus(StatusAttemper::Abnormal);
        }
        else if (int_value == normal_value_) {
            //正常
            setStatus(StatusAttemper::Normal);
        }
        else {
            //未知
            setStatus(StatusAttemper::Unknown);
        }
    }
}
