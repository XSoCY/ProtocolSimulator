#include "bitcombobox.h"
#include <QEvent>

BitCombobox::BitCombobox(const QDomElement &doc_element, QWidget *parent) : QComboBox(parent)
{
    value_start_bit_ = doc_element.attribute("value_start_bit").toInt();
    value_bit_len_   = doc_element.attribute("value_bit_len").toInt();

    QDomNode docNode = doc_element.firstChild();
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString strTagName = sub_doc_element.tagName();
            if (strTagName == "Item") {
                auto label = sub_doc_element.attribute("label");
                auto data  = sub_doc_element.attribute("data");
                if (data.startsWith("0x", Qt::CaseInsensitive)) {
                    auto hex_value = data.mid(2).toUInt(nullptr, 16);
                    addItem(label, hex_value);
                }
                else {
                    auto int_value = data.toUInt();
                    addItem(label, int_value);
                }
            }
        }
        docNode = docNode.nextSibling();
    }

    installEventFilter(this);

    connect(this,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            [=](int index) { emit currentDataChanged(paramVaule()); });
}

QVariant BitCombobox::paramVaule() const
{
    auto int_value     = currentData().toULongLong();
    auto convert_value = int_value << value_start_bit_;
    return convert_value;
}

void BitCombobox::setParamVaule(const QVariant &param_vaule)
{
    if (!param_vaule.canConvert<qulonglong>()) {
        return;
    }
    auto int_value     = param_vaule.toULongLong();
    auto convert_value = (int_value >> value_start_bit_) & ((1 << value_bit_len_) - 1);
    setCurrentIndex(findData(convert_value));
    if (!first_setting_) {
        emit currentDataChanged(convert_value);
        first_setting_ = true;
    }
}

bool BitCombobox::editMode() const
{
    return edit_mode_;
}

void BitCombobox::setEditMode(bool edit_mode)
{
    edit_mode_ = edit_mode;
}

bool BitCombobox::eventFilter(QObject *obj, QEvent *event)
{
    if (edit_mode_) {
        return QObject::eventFilter(obj, event);
    }
    if (event->type() == QEvent::Wheel) {
        return true;
    }
    else if (event->type() == QEvent::KeyPress) {
        return true;
    }
    else if (event->type() == QEvent::KeyRelease) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonDblClick) {
        return true;
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}
