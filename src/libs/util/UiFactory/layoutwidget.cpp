#include "layoutwidget.h"
#include "actionfactory.h"
#include "conditonfactory.h"
#include "uifactory.h"
#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QMetaProperty>
#include <QVBoxLayout>
#include <QVariant>

Q_DECLARE_METATYPE(ParamItem)

LayoutWidget::LayoutWidget(const QDomElement &ui_xml,
                           const QDomElement &relation_xml,
                           QWidget *parent)
    : QWidget(parent)
{
    initUI(ui_xml);
    initRelation(relation_xml);

    for(auto param_id : m_param_id_to_widget_input_property_name.keys()){
        auto widget_input_property_name_list =
            m_param_id_to_widget_input_property_name.values(param_id);
        for (auto widget_input_property_name : widget_input_property_name_list) {
            auto widget              = widget_input_property_name.first;
            auto input_property_name = widget_input_property_name.second;
            // 连接关系，部件的值变化，通知本布局控件
            connectRelation(widget, input_property_name);
            // 设置窗口属性
            widget->setProperty(input_property_name.toStdString().c_str(),
                                widget->property(input_property_name.toStdString().c_str()));
        }
    }
}

QVariant LayoutWidget::paramVaule() const
{
    return getSettingValue();
}

void LayoutWidget::setParamVaule(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<QMap<QString, QVariant>>()) {
        current_status_value_ = param_vaule.toMap();
        setValue(current_status_value_);
        updateUI();
    }
}

QVariant LayoutWidget::comparedValue() const
{
    return compared_value_;
}

void LayoutWidget::setComparedValue(const QVariant &param_vaule)
{
    compared_value_ = param_vaule.toMap();
    updateUI();
}

bool LayoutWidget::editMode() const
{
    return is_edit_mode_;
}

void LayoutWidget::setEditMode(const bool editmode)
{
    is_edit_mode_ = editmode;

    for (auto widget_input_property_name_ : m_param_id_to_widget_input_property_name) {
        auto widget = widget_input_property_name_.first;
        if (widget) {
            widget->setProperty("editMode", is_edit_mode_);
        }
    }
}

void LayoutWidget::showEvent(QShowEvent *event)
{
    for (auto param_id : param_id_to_label_.keys()) {
        auto label = param_id_to_label_.value(param_id);
        if (label) {
            auto pal = palette();
            label->setPalette(pal);
        }
    }
    compared_value_.clear();
    QWidget::showEvent(event);
}

void LayoutWidget::initUI(const QDomElement &dom_element)
{
    auto v_layout = new QVBoxLayout;
    v_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(v_layout);

    QDomNode docNode = dom_element.firstChild();

    if (docNode.isNull()) {

        auto label = new QLabel("暂无参数");
        label->setAlignment(Qt::AlignCenter);
        v_layout->addWidget(label);
    }

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            QWidget *widget  = nullptr;
            if (tag_name == "Widget") {
                widget = createWidgetItem(sub_doc_element);
            }
            else if (tag_name == "MultiWidget") {
                widget = createMultiWidgetItem(sub_doc_element);
            }
            else if (tag_name == "GroupBox") {
                widget = createGroupBox(sub_doc_element);
            }
            else if (tag_name == "GridLayout") {
                widget = createGridLayout(sub_doc_element);
            }
            else if (tag_name == "HLayout") {
                widget = createHLayout(sub_doc_element);
            }
            else if (tag_name == "VLayout") {
                widget = createVLayout(sub_doc_element);
            }
            if (widget) {
                v_layout->addWidget(widget);
            }
        }
        docNode = docNode.nextSibling();
    }
    v_layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void LayoutWidget::initRelation(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return;
    }

    QDomNode docNode = dom_element.firstChild();

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            if (tag_name == "Relation") {
                auto param_id       = sub_doc_element.attribute("paramID");
                auto condition_type = sub_doc_element.attribute("conditionType");
                auto condition      = std::shared_ptr<IConditonProduct>(
                    ConditonFactory::instance().createProduct(condition_type, sub_doc_element));
                auto action_list = initExcuteAction(sub_doc_element);

                param_id_to_condition_action_list.insert(param_id,
                                                         qMakePair(condition, action_list));

                auto widget_input_property_name_list =
                    m_param_id_to_widget_input_property_name.values(param_id);

                for (auto widget_input_property_name : widget_input_property_name_list) {
                    auto widget              = widget_input_property_name.first;
                    auto input_property_name = widget_input_property_name.second;
                    connectRelation(widget, input_property_name);
                }
            }
        }
        docNode = docNode.nextSibling();
    }
}

QList<std::shared_ptr<IActionProduct>>
LayoutWidget::initExcuteAction(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return QList<std::shared_ptr<IActionProduct>>();
    }

    QList<std::shared_ptr<IActionProduct>> action_list;

    QDomNode docNode = dom_element.firstChild();

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            if (tag_name == "Action") {
                auto action_product = std::shared_ptr<IActionProduct>(
                    ActionFactory::instance().createProduct("property", sub_doc_element));
                action_list.append(action_product);
            }
        }
        docNode = docNode.nextSibling();
    }

    return action_list;
}

void LayoutWidget::connectRelation(QWidget *widget, const QString &input_property_name)
{
    auto meta_object   = widget->metaObject();
    auto meta_property = meta_object->property(
        meta_object->indexOfProperty(input_property_name.toStdString().c_str()));
    auto meta_method = meta_property.notifySignal();

    auto this_meta_object = metaObject();
    auto slot_index       = this_meta_object->indexOfMethod(
        this_meta_object->normalizedSignature("onWidgetPropertyChanged(const QVariant&)").data());
    auto meta_method_slot = this_meta_object->method(slot_index);
    connect(widget, meta_method, this, meta_method_slot, Qt::UniqueConnection);
}

QWidget *LayoutWidget::createMultiWidgetItem(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }
    auto main_widget = new QWidget;
    auto h_layout    = new QHBoxLayout;
    h_layout->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(h_layout);

    auto type              = dom_element.attribute("type");
    auto relation_param_id = dom_element.attribute("relationParamID");
    auto label             = dom_element.attribute("label");

    if (!label.isEmpty()) {
        auto label_widget = new QLabel(label);
        h_layout->addWidget(label_widget);
        param_id_to_label_.insert(relation_param_id, label_widget);
    }

    // Multi widget 不进入参数关联， 不加入
    // param_id_to_label_、widget_to_param_id_、param_id_to_widget_ 的map
    auto widget = UiFactory::instance().createProduct(type, dom_element);
    if (widget) {
        widget->setProperty("editMode", false);
        widget_to_param_id_.insert(widget, relation_param_id);
        param_id_to_widget_.insert(relation_param_id, widget);

        QDomNode docNode = dom_element.firstChild();
        while (!docNode.isNull()) {
            QDomElement sub_doc_element = docNode.toElement();
            if (!sub_doc_element.isNull()) {
                QString tag_name = sub_doc_element.tagName();
                if (tag_name == "Param") {
                    auto param_id            = sub_doc_element.attribute("paramID");
                    auto input_property_name = sub_doc_element.attribute("inputProperty");
                    m_param_id_to_widget_input_property_name.insert(
                        param_id, qMakePair(widget, input_property_name));
                }
            }
            docNode = docNode.nextSibling();
        }
    }
    h_layout->addWidget(widget);

    return main_widget;
}

QWidget *LayoutWidget::createWidgetItem(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }
    auto main_widget = new QWidget;
    auto h_layout    = new QHBoxLayout;
    h_layout->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(h_layout);

    ParamItem param;
//    param.paramID = dom_element.attribute("paramID");
//    param.widgetType = dom_element.attribute("widgetType");
//    param.dataType = dom_element.attribute("dataType");
//    param.inputProperty = dom_element.attribute("inputProperty");
//    param.label = dom_element.attribute("label");
//    param.coefficient = dom_element.attribute("coefficient");
//    param.decimal = dom_element.attribute("decimal");
//    param.defaultValue = dom_element.attribute("defaultValue");
//    param.curValue = param.defaultValue;
//    param.min = dom_element.attribute("min");
//    param.max = dom_element.attribute("max");
    memcpy(param.paramID, dom_element.attribute("paramID").toStdString().c_str(), sizeof(param.paramID));
    memcpy(param.widgetType, dom_element.attribute("widgetType").toStdString().c_str(), sizeof(param.widgetType));
    memcpy(param.dataType, dom_element.attribute("dataType").toStdString().c_str(), sizeof(param.dataType));
    memcpy(param.inputProperty, dom_element.attribute("inputProperty").toStdString().c_str(), sizeof(param.inputProperty));
    memcpy(param.label, dom_element.attribute("label").toStdString().c_str(), sizeof(param.label));
    memcpy(param.coefficient, dom_element.attribute("coefficient").toStdString().c_str(), sizeof(param.coefficient));
    memcpy(param.decimal, dom_element.attribute("decimal").toStdString().c_str(), sizeof(param.decimal));
    memcpy(param.defaultValue, dom_element.attribute("defaultValue").toStdString().c_str(), sizeof(param.defaultValue));
    memcpy(param.curValue, dom_element.attribute("defaultValue").toStdString().c_str(), sizeof(param.curValue));
    memcpy(param.min, dom_element.attribute("min").toStdString().c_str(), sizeof(param.min));
    memcpy(param.max, dom_element.attribute("max").toStdString().c_str(), sizeof(param.max));

//    if (!param.label.isEmpty()) {
//        auto label_widget = new QLabel(param.label);
//        h_layout->addWidget(label_widget, 1);
//        param_id_to_label_.insert(param.paramID, label_widget);
//    }
    QString paramID = QString::fromUtf8(param.paramID);
    QString label = QString::fromUtf8(param.label);
    QString widgetType = QString::fromUtf8(param.widgetType);
    QString inputProperty = QString::fromUtf8(param.inputProperty);
    if (!QString::fromUtf8(param.label).isEmpty()) {
        auto label_widget = new QLabel(label);
        h_layout->addWidget(label_widget, 1);
        param_id_to_label_.insert(paramID, label_widget);
    }
    auto widget = UiFactory::instance().createProduct(widgetType, dom_element);
    if (widget) {
        //设置编辑模式属性值
        widget->setProperty("editMode", false);
        //设置输入属性值
        QVariant var;
        var.fromValue(param);
        widget->setProperty(param.inputProperty, var);
        widget_to_param_id_.insert(widget, paramID);
        param_id_to_widget_.insert(paramID, widget);
        m_param_id_to_widget_input_property_name.insert(paramID,
                                                       qMakePair(widget, inputProperty));
    }
    h_layout->addWidget(widget, 1);

    return main_widget;
}

QWidget *LayoutWidget::createGroupBox(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }
    auto text     = dom_element.attribute("text");
    auto groupbox = new QGroupBox(text);
    auto layout   = new QHBoxLayout;
    layout->setContentsMargins(6, 6, 6, 6);
    groupbox->setLayout(layout);

    QWidget *widget  = nullptr;
    auto layout_type = dom_element.attribute("layoutType");
    if (layout_type == "GridLayout") {
        widget = createGridLayout(dom_element);
    }
    else if (layout_type == "HLayout") {
        widget = createHLayout(dom_element);
    }
    else if (layout_type == "VLayout") {
        widget = createVLayout(dom_element);
    }
    if (widget) {
        layout->addWidget(widget);
    }
    return groupbox;
}

void LayoutWidget::onWidgetPropertyChanged(const QVariant &value)
{
    if (auto widget = qobject_cast<QWidget *>(sender())) {
        auto param_id = widget_to_param_id_.value(widget);

        qDebug() << "sender" << sender() << "改变" << param_id << value;
        auto condition_action_list_list = param_id_to_condition_action_list.values(param_id);

        for (auto condition_action_list : condition_action_list_list) {
            auto condition   = condition_action_list.first;
            auto action_list = condition_action_list.second;

            if (condition.get() && condition->judge(value)) {
                for (auto action : action_list) {
                    if (action.get()) {
                        action->excute(param_id_to_widget_);
                        action->excute(param_id_to_label_);
                    }
                }
            }
        }
    }
}

void LayoutWidget::updateUI()
{
    QStringList remove_params;
    for (auto param_id : compared_value_.keys()) {
        auto setting_value = compared_value_.value(param_id);

        auto current_status_value = current_status_value_.value(param_id);

        auto label = param_id_to_label_.value(param_id);
        if (label) {
            if (current_status_value == setting_value) {
                auto pal = label->palette();
                pal.setColor(QPalette::WindowText, QColor(34, 177, 76));
                label->setPalette(pal);
                remove_params.append(param_id);
            }
            else {
                auto pal = label->palette();
                pal.setColor(QPalette::WindowText, QColor(Qt::red));
                label->setPalette(pal);
            }
        }
    }

    for (auto remove_param_id : remove_params) {
        compared_value_.remove(remove_param_id);
    }
}

QWidget *LayoutWidget::createGridLayout(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }
    auto main_widget = new QWidget;
    auto layout      = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(layout);

    auto row_cnt     = dom_element.attribute("rowCount").toInt();
    auto no_spacer   = dom_element.attribute("noSpacer").toInt();
    QDomNode docNode = dom_element.firstChild();

    int widget_index = 0;
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            QWidget *widget  = nullptr;
            if (tag_name == "Widget") {
                widget = createWidgetItem(sub_doc_element);
            }
            else if (tag_name == "MultiWidget") {
                widget = createMultiWidgetItem(sub_doc_element);
            }
            else if (tag_name == "GroupBox") {
                widget = createGroupBox(sub_doc_element);
            }
            else if (tag_name == "GridLayout") {
                widget = createGridLayout(sub_doc_element);
            }
            else if (tag_name == "HLayout") {
                widget = createHLayout(sub_doc_element);
            }
            else if (tag_name == "VLayout") {
                widget = createVLayout(sub_doc_element);
            }
            else if (tag_name == "SpaceItem") {
                ++widget_index;
            }

            auto rowSpan = sub_doc_element.attribute("rowSpan", "1").toInt();
            auto row =
                sub_doc_element.attribute("row", QString::number(int(widget_index % row_cnt)))
                    .toInt();
            auto col =
                sub_doc_element.attribute("col", QString::number(int(widget_index / row_cnt)))
                    .toInt();

            if (widget) {
                layout->addWidget(widget, row, col, rowSpan, 1);
                widget_index += rowSpan;
            }
        }
        docNode = docNode.nextSibling();
    }

    if (no_spacer != 1) {
        layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum),
                        0,
                        layout->columnCount());
    }
    return main_widget;
}

QWidget *LayoutWidget::createHLayout(const QDomElement &dom_element)
{
    if (dom_element.isNull()) {
        return nullptr;
    }
    auto main_widget = new QWidget;
    auto layout      = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(layout);

    QDomNode docNode = dom_element.firstChild();

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            QWidget *widget  = nullptr;
            if (tag_name == "Widget") {
                widget = createWidgetItem(sub_doc_element);
            }
            else if (tag_name == "MultiWidget") {
                widget = createMultiWidgetItem(sub_doc_element);
            }
            else if (tag_name == "GroupBox") {
                widget = createGroupBox(sub_doc_element);
            }
            else if (tag_name == "GridLayout") {
                widget = createGridLayout(sub_doc_element);
            }
            else if (tag_name == "HLayout") {
                widget = createHLayout(sub_doc_element);
            }
            else if (tag_name == "VLayout") {
                widget = createVLayout(sub_doc_element);
            }
            else if (tag_name == "Spacer") {
                layout->addItem(
                    new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
            }
            if (widget) {
                layout->addWidget(widget);
            }
        }
        docNode = docNode.nextSibling();
    }

    return main_widget;
}

QWidget *LayoutWidget::createVLayout(const QDomElement &dom_element)
{

    if (dom_element.isNull()) {
        return nullptr;
    }
    auto main_widget = new QWidget;
    auto layout      = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(layout);

    QDomNode docNode = dom_element.firstChild();

    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            QWidget *widget  = nullptr;
            if (tag_name == "Widget") {
                widget = createWidgetItem(sub_doc_element);
            }
            else if (tag_name == "MultiWidget") {
                widget = createMultiWidgetItem(sub_doc_element);
            }
            else if (tag_name == "GroupBox") {
                widget = createGroupBox(sub_doc_element);
            }
            else if (tag_name == "GridLayout") {
                widget = createGridLayout(sub_doc_element);
            }
            else if (tag_name == "HLayout") {
                widget = createHLayout(sub_doc_element);
            }
            else if (tag_name == "VLayout") {
                widget = createVLayout(sub_doc_element);
            }
            else if (tag_name == "Spacer") {
                layout->addItem(
                    new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
            }
            if (widget) {
                layout->addWidget(widget);
            }
        }
        docNode = docNode.nextSibling();
    }

    return main_widget;
}

void LayoutWidget::setValue(const QMap<QString, QVariant> &param_id_to_value)
{
    for (QString param_id : m_param_id_to_widget_input_property_name.keys()) {
        QList<QPair<QWidget *, QString>>  widget_input_property_name_list = m_param_id_to_widget_input_property_name.values(param_id);
        for (QPair<QWidget *, QString> widget_input_property_name : widget_input_property_name_list) {
            QWidget * widget = widget_input_property_name.first;
            if (widget) {
                QString input_property_name = widget_input_property_name.second;
                QVariant value = param_id_to_value.value(param_id);
                widget->setProperty(input_property_name.toStdString().c_str(), value);
            }
        }
    }
}

QMap<QString, QVariant> LayoutWidget::getSettingValue() const
{
    QMap<QString, QVariant> map;

//    for (auto param_id : m_param_id_to_widget_input_property_name.keys()) {
//        auto widget_input_property_name_list =
//            m_param_id_to_widget_input_property_name.values(param_id);
//        for (auto widget_input_property_name : widget_input_property_name_list) {
//            auto widget = widget_input_property_name.first;
//            if (widget) {
//                auto input_property_name = widget_input_property_name.second;
//                auto std_str             = input_property_name.toStdString();
//                auto value               = widget->property(std_str.c_str());
//                if (map.contains(param_id) && map.value(param_id).canConvert<qulonglong>()
//                    && value.canConvert<qulonglong>()) {
//                    auto map_value = map.value(param_id).toULongLong();
//                    auto int_value = value.toULongLong();
//                    value          = int_value | map_value;
//                }
//                map.insert(param_id, value);
//            }
//        }
//    }

    for (QString param_id : m_param_id_to_widget_input_property_name.keys()) {
        QList<QPair<QWidget *, QString>> widget_input_property_name_list = m_param_id_to_widget_input_property_name.values(param_id);
        for (QPair<QWidget *, QString> widget_input_property_name : widget_input_property_name_list) {
            QWidget * widget = widget_input_property_name.first;
            if (widget) {
                QString input_property_name = widget_input_property_name.second;
                QVariant value = widget->property(input_property_name.toStdString().c_str());
                // 所有参数控件的参数更新到map
                map.insert(param_id, value);
            }
        }
    }

    return map;
}
