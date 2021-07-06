#include "modeswitchwidget.h"
#include "uifactory.h"
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QVariant>

ModeSwitchWidget::ModeSwitchWidget(const QDomElement& doc_element, QWidget* parent) : QWidget(parent)
{
    initUI(doc_element);
}

QVariant ModeSwitchWidget::paramVaule() const
{
    auto mode_head = combobox_->currentData();
    if (!mode_head_value_to_widget_.contains(mode_head.toUInt())) {
        return QVariant();
    }

    if (auto widget = mode_head_value_to_widget_.value(mode_head.toUInt())) {
        QVariantList variant_list;
        variant_list << mode_head << widget->property("paramVaule");
        return variant_list;
    }

    return QVariant();
}

void ModeSwitchWidget::setParamVaule(const QVariant& param_vaule)
{
    if (!param_vaule.canConvert<QVariantList>()) {
        return;
    }
    auto variant_list = param_vaule.toList();
    if (variant_list.size() != 2) {
        return;
    }
    auto mode_head             = variant_list.at(0);
    auto sub_param_id_to_value = variant_list.at(1).toMap();

    if (combobox_) {
        combobox_->setCurrentIndex(combobox_->findData(mode_head));
    }

    if (!mode_head_value_to_widget_.contains(mode_head.toUInt())) {
        return;
    }
    if (auto widget = mode_head_value_to_widget_.value(mode_head.toUInt())) {
        widget->setProperty("paramVaule", sub_param_id_to_value);
    }
}

bool ModeSwitchWidget::editMode() const
{
    return combobox_->isEnabled();
}

void ModeSwitchWidget::setEditMode(const bool editmode)
{
    combobox_->setEnabled(editmode);
    for (auto widget : mode_head_value_to_widget_) {
        if (widget) {
            widget->setProperty("editMode", editmode);
        }
    }
}

void ModeSwitchWidget::initUI(const QDomElement& doc_element)
{

    if (doc_element.isNull()) {
        return;
    }

    auto head_text  = doc_element.attribute("Headlabel");
    auto group_text = doc_element.attribute("GroupBoxLabel");

    auto layout = new QVBoxLayout;

    auto h_layout   = new QHBoxLayout;
    combobox_       = new QComboBox;
    auto head_label = new QLabel(head_text);

    h_layout->addWidget(head_label);
    h_layout->addWidget(combobox_);

    auto groupbox        = new QGroupBox(group_text);
    auto groupbox_layout = new QVBoxLayout;
    groupbox->setLayout(groupbox_layout);
    auto stacked_widget = new QStackedWidget;
    groupbox_layout->addWidget(stacked_widget);

    layout->addLayout(h_layout);
    layout->addWidget(groupbox);

    setLayout(layout);

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
                    combobox_->addItem(label, hex_value);

                    auto widget = UiFactory::instance().createProduct("LayoutWidget", sub_doc_element);
                    mode_head_value_to_widget_.insert(hex_value, widget);
                    stacked_widget->addWidget(widget);
                }
                else {
                    auto int_value = data.toUInt();
                    combobox_->addItem(label, int_value);

                    auto widget = UiFactory::instance().createProduct("LayoutWidget", sub_doc_element);
                    mode_head_value_to_widget_.insert(int_value, widget);
                    stacked_widget->addWidget(widget);
                }
            }
        }
        docNode = docNode.nextSibling();
    }

    connect(combobox_, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), stacked_widget,
            &QStackedWidget::setCurrentIndex);
}
