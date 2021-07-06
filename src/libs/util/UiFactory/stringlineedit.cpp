#include "stringlineedit.h"
#include <QTextCodec>

StringLineEdit::StringLineEdit(const QDomElement &doc_element, QWidget *parent) : QLineEdit(parent)
{
    len_    = doc_element.attribute("len").toInt();
    encode_ = doc_element.attribute("encode", "UTF-8");
    setMaxLength(len_);
}

QVariant StringLineEdit::paramVaule() const
{
    QTextCodec *utf8   = QTextCodec::codecForName("UTF-8");
    QTextCodec *encode = QTextCodec::codecForName(encode_.toStdString().c_str());

    if (!encode) {
        return QVariant();
    }

    auto unicode_str = encode->toUnicode(text().toStdString().c_str());
    auto utf8_str    = utf8->fromUnicode(unicode_str);

    QByteArray value = utf8_str.leftJustified(len_, '\0');
    return value;
}

void StringLineEdit::setParamVaule(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<QByteArray>()) {
        auto value = param_vaule.toByteArray();

        QTextCodec *utf8   = QTextCodec::codecForName("UTF-8");
        QTextCodec *encode = QTextCodec::codecForName(encode_.toStdString().c_str());

        if (!encode) {
            return;
        }
        auto unicode_str = encode->toUnicode(value);
        auto utf8_str    = utf8->fromUnicode(unicode_str);
        setText(utf8_str);
    }
}
