#include "paramlisttablewidget.h"
#include "uifactory.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>

ParamListTableWidget::ParamListTableWidget(const QDomElement &doc_element, QWidget *parent)
    : QWidget(parent)
{
    initUI(doc_element);
}

QVariant ParamListTableWidget::paramVaule() const
{
    QMap<int, QMap<QString, QVariant>> loop_index_to_param_map;

    for (auto loop_index_sub_param_id :
         loop_index_sub_param_id_to_widget_input_property_name_.keys()) {
        auto loop_index = loop_index_sub_param_id.first;

        if (loop_index >= loop_size_->value()) {
            break;
        }
        auto sub_param_id = loop_index_sub_param_id.second;
        auto widget_input_property_name =
            loop_index_sub_param_id_to_widget_input_property_name_.value(loop_index_sub_param_id);
        auto widget              = widget_input_property_name.first;
        auto input_property_name = widget_input_property_name.second;

        if (widget) {
            auto std_str = input_property_name.toStdString();
            auto value   = widget->property(std_str.c_str());

            auto &param_map = loop_index_to_param_map[loop_index];
            param_map.insert(sub_param_id, value);
        }
    }

    auto value_list = loop_index_to_param_map.values();

    return QVariant::fromValue<decltype(value_list)>(value_list);
}

void ParamListTableWidget::setParamVaule(const QVariant &param_vaule)
{
    if (!param_vaule.canConvert<QList<QVariant>>()) {
        return;
    }

    auto loop_param_value_list = param_vaule.value<QList<QVariant>>();
    auto loop_size_value       = QVariant(loop_param_value_list.size());

    if (loop_size_) {
        loop_size_->setValue(loop_param_value_list.size());
    }
    for (int i = 0; i < loop_param_value_list.size(); ++i) {
        auto loop_param_value = loop_param_value_list.at(i).toMap();
        for (auto sub_param_id : loop_param_value.keys()) {

            auto value = loop_param_value.value(sub_param_id);
            auto widget_input_property_name =
                loop_index_sub_param_id_to_widget_input_property_name_.value(
                    qMakePair(i, sub_param_id));

            auto widget              = widget_input_property_name.first;
            auto input_property_name = widget_input_property_name.second;

            if (widget) {
                auto std_str = input_property_name.toStdString();
                widget->setProperty(std_str.c_str(), value);
            }
        }
    }
}

bool ParamListTableWidget::editMode() const
{
    return !loop_size_->isReadOnly();
}

void ParamListTableWidget::setEditMode(const bool editmode)
{
    loop_size_->setReadOnly(!editmode);

    for (auto widget_input_property_name : loop_index_sub_param_id_to_widget_input_property_name_) {
        auto widget = widget_input_property_name.first;
        if (widget) {
            widget->setProperty("editMode", editmode);
        }
    }
}

void ParamListTableWidget::initUI(const QDomElement &doc_element)
{
    auto main_layout  = new QVBoxLayout;
    int max_loop_size = doc_element.attribute("maxLoopSize").toInt();

    if (!loop_size_) {
        loop_size_ = new QSpinBox;
        loop_size_->setRange(0, max_loop_size);
    }
    auto h_layout = new QHBoxLayout;
    h_layout->addWidget(new QLabel("总数:"));
    h_layout->addWidget(loop_size_);
    h_layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(h_layout);
    auto table = new QTableWidget;
    main_layout->addWidget(table);

    table->setRowCount(max_loop_size);
    setLayout(main_layout);

    QDomNode docNode = doc_element.firstChild();

    int col_index = 0;
    auto titles   = QStringList();

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            if (tag_name == "Widget") {

                auto param_id            = sub_doc_element.attribute("paramID");
                auto input_property_name = sub_doc_element.attribute("inputProperty");
                auto label               = sub_doc_element.attribute("label");

                titles << label;
                table->setColumnCount(titles.size());
                for (int row = 0; row < max_loop_size; ++row) {
                    if (auto widget = createWidgetItem(sub_doc_element)) {
                        table->setCellWidget(row, col_index, widget);
                        loop_index_sub_param_id_to_widget_input_property_name_.insert(
                            qMakePair(row, param_id), qMakePair(widget, input_property_name));
                    }
                }
            }
        }
        docNode = docNode.nextSibling();
        ++col_index;
    }

    table->setHorizontalHeaderLabels(titles);
    for (int row = 0; row < max_loop_size; ++row) {
        table->setRowHidden(row, true);
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(loop_size_,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,
            [=](int value) {
                if (table) {
                    for (int row = 0; row < max_loop_size; ++row) {
                        table->setRowHidden(row, row >= value);
                    }
                }
            });
}

QWidget *ParamListTableWidget::createWidgetItem(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }

    auto type                = dom_element.attribute("type");
    auto param_id            = dom_element.attribute("paramID");
    auto input_property_name = dom_element.attribute("inputProperty");
    auto label               = dom_element.attribute("label");

    auto widget = UiFactory::instance().createProduct(type, dom_element);
    if (widget) {
        widget->setProperty("editMode", false);
    }
    return widget;
}
