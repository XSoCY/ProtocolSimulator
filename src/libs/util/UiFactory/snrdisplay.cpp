#include "snrdisplay.h"
#include <cmath>
#include <QDebug>

SNRDisplay::SNRDisplay(const QDomElement &doc_element, QWidget *parent) : QLabel(parent)
{
    init(doc_element);
}

QVariant SNRDisplay::paramVaule() const
{
    return QVariant();
}

void SNRDisplay::setParamVaule(const QVariant &param_vaule)
{
    if (!param_vaule.canConvert<QByteArray>()){
        return;
    }
    auto bytearray = param_vaule.toByteArray();


    if (signal_start_ % 8 != 0 || signal_len_ % 8 != 0 || noise_start_ % 8 != 0 || noise_len_ % 8 != 0) {
        qDebug() << "不支持当前配置";
    }

    qint64 signal = 0;

    auto signal_start_byte = signal_start_ / 8;
    auto signal_len_byte = signal_len_ / 8;

    memcpy(reinterpret_cast<char*>(&signal), bytearray.data() + signal_start_byte, static_cast<size_t>(signal_len_byte));

    qint64 noise = 0;

    auto noise_start_byte = noise_start_ / 8;
    auto noise_len_byte = noise_len_ / 8;

    memcpy(reinterpret_cast<char*>(&noise), bytearray.data() + noise_start_byte, static_cast<size_t>(noise_len_byte));

    double snr = 10 * (log10(signal) - log10(noise));

    setText(QString::number(snr, 'f', 2));
}

void SNRDisplay::init(const QDomElement &doc_element)
{
    QDomNode docNode = doc_element.firstChild();
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString strTagName = sub_doc_element.tagName();
            if (strTagName == "Signal") {
                signal_start_ = sub_doc_element.attribute("startBit").toInt();
                signal_len_  = sub_doc_element.attribute("len").toInt();
            } else if (strTagName == "Noise") {
                noise_start_ = sub_doc_element.attribute("startBit").toInt();
                noise_len_  = sub_doc_element.attribute("len").toInt();
            }
        }
        docNode = docNode.nextSibling();
    }
}
