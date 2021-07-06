#include "hexlineedit.h"
#include <QRegExp>
#include <QRegExpValidator>

HexLineEdit::HexLineEdit(const QDomElement& doc_element, QWidget* parent) : QLineEdit(parent)
{
    len_ = doc_element.attribute("len").toInt();
    auto encryption = doc_element.attribute("encryption", 0).toInt();
    encryption_ = (encryption != 0);

    QRegExp regExp(QString("[a-fA-F0-9]{%1}").arg(len_ * 2));
    setPlaceholderText(QString("%1字节16进制数").arg(len_));
    setValidator(new QRegExpValidator(regExp, this));
}

QVariant HexLineEdit::paramVaule() const
{
    if (encryption_){
        auto value = convSPolyToSaveData(text().toUShort(nullptr, 16));
        return value;
    } else {
        auto value = text().toULongLong(nullptr, 16);
        return value;
    }
}

void HexLineEdit::setParamVaule(const QVariant& param_vaule)
{
    if (param_vaule.canConvert<qulonglong>()) {
        if (encryption_){
            auto    value     = param_vaule.toULongLong(nullptr);

            auto u16_value = static_cast<quint16>(value);
            QString str_value = QString::number(convSPolyToShowData(u16_value), 16);
            setText(str_value);
        } else {
            auto    value     = param_vaule.toULongLong(nullptr);
            QString str_value = QString::number(value, 16);
            setText(str_value);
        }
    }
}

quint16 HexLineEdit::convSPolyToSaveData(quint16 show_data) const
{
    quint16 ret =0;

    for (int i = 0; i < 10; ++i){
        if ((9 - 2 * i) > 0){
            ret |= ((show_data & (1 << (9 - i))) >> (9 - 2 * i));
        } else {
            ret |= ((show_data & (1 << (9 - i))) << (2 * i - 9));
        }
    }

    ret = (ret << 1) | 1;

    return ret;
}

quint16 HexLineEdit::convSPolyToShowData(quint16 save_data) const
{
    quint16 ret =0;

    save_data = save_data >> 1;

    for (int i = 0; i < 10; ++i){
        if ((9 - 2 * i) >= 0){
            ret |= ((save_data & (1 << (9 - i))) >> (9 - 2 * i));
        } else {
            ret |= ((save_data & (1 << (9 - i))) << (2 * i - 9));
        }
    }
    return ret;
}
