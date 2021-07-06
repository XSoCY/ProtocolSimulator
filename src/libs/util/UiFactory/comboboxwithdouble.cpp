#include "comboboxwithdouble.h"
#include <QComboBox>
#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>

ComboboxWithDouble::ComboboxWithDouble(const QDomElement& doc_element, QWidget* parent)
{
    initUI();
    initXml(doc_element);

    main_widget_->installEventFilter(this);
    sub_widget_->installEventFilter(this);

    connect(main_widget_, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            [=](int index) { emit currentDataChanged(paramVaule()); });

    connect(sub_widget_, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            [=](int index) { emit currentDataChanged(paramVaule()); });
}

QVariant ComboboxWithDouble::paramVaule() const
{
    auto main_value = main_widget_->currentData().toInt();
    auto sub_value  = sub_widget_->currentData().toInt();

    quint8 value = 0;
    value        = value | (main_value << 0);
    value        = value | (sub_value << 4);
    return value;
}

void ComboboxWithDouble::setParamVaule(const QVariant& param_vaule)
{
    if (!param_vaule.canConvert<quint8>()) {
        return;
    }
    auto value      = param_vaule.value<quint8>();
    auto main_value = (value >> 0) & ((1 << 4) - 1);
    auto sub_value  = (value >> 4) & ((1 << 4) - 1);
    if (main_widget_) {
        main_widget_->setCurrentIndex(main_widget_->findData(main_value));
    }
    if (sub_widget_) {
        sub_widget_->setCurrentIndex(sub_widget_->findData(sub_value));
    }
    if (!first_setting_) {
        emit currentDataChanged(param_vaule);
        first_setting_ = true;
    }
}

bool ComboboxWithDouble::editMode() const
{
    return edit_mode_;
}

void ComboboxWithDouble::setEditMode(bool edit_mode)
{
    edit_mode_ = edit_mode;
}

bool ComboboxWithDouble::eventFilter(QObject* obj, QEvent* event)
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

void ComboboxWithDouble::initUI()
{
    if (!main_widget_) {
        main_widget_ = new QComboBox(this);
    }
    if (!sub_widget_) {
        sub_widget_ = new QComboBox(this);
    }
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(new QLabel("主"), 0);
    layout->addWidget(main_widget_, 1);
    layout->addWidget(new QLabel("副"), 0);
    layout->addWidget(sub_widget_, 1);

    setLayout(layout);
}

void ComboboxWithDouble::initXml(const QDomElement& doc_element)
{
    QDomNode docNode = doc_element.firstChild();
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString strTagName = sub_doc_element.tagName();
            if (strTagName == "MainWidget") {
                initWidget(sub_doc_element, main_widget_);
            }
            else if (strTagName == "SubWidget") {
                initWidget(sub_doc_element, sub_widget_);
            }
        }
        docNode = docNode.nextSibling();
    }
}

void ComboboxWithDouble::initWidget(const QDomElement& doc_element, QComboBox* combobox)
{
    if (!combobox) {
        return;
    }
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
                    combobox->addItem(label, hex_value);
                }
                else {
                    auto int_value = data.toUInt();
                    combobox->addItem(label, int_value);
                }
            }
        }
        docNode = docNode.nextSibling();
    }
}
