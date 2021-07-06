#include "integerspinbox.h"
#include "uifactory.h"

Q_DECLARE_METATYPE(ParamItem)

IntegerSpinBox::IntegerSpinBox(const QDomElement &doc_element, QWidget *parent) : QSpinBox(parent)
{
    m_coefficient = doc_element.attribute("coefficient", "1").toInt();
    m_init_value = doc_element.attribute("defaultValue", "0").toInt();
    m_min = doc_element.attribute("min", "0").toInt();
    m_max = doc_element.attribute("max", "0").toInt();
    memcpy(m_param.paramID, doc_element.attribute("paramID").toStdString().c_str(), sizeof(m_param.paramID));
    memcpy(m_param.widgetType, doc_element.attribute("widgetType").toStdString().c_str(), sizeof(m_param.widgetType));
    memcpy(m_param.dataType, doc_element.attribute("dataType").toStdString().c_str(), sizeof(m_param.dataType));
    memcpy(m_param.inputProperty, doc_element.attribute("inputProperty", "paramValue").toStdString().c_str(), sizeof(m_param.inputProperty));
    memcpy(m_param.label, doc_element.attribute("label").toStdString().c_str(), sizeof(m_param.label));
    memcpy(m_param.coefficient, doc_element.attribute("coefficient", "1").toStdString().c_str(), sizeof(m_param.coefficient));
    memcpy(m_param.decimal, doc_element.attribute("decimal", "0").toStdString().c_str(), sizeof(m_param.decimal));
    memcpy(m_param.defaultValue, doc_element.attribute("defaultValue", "1").toStdString().c_str(), sizeof(m_param.defaultValue));
    memcpy(m_param.curValue, doc_element.attribute("defaultValue", "0").toStdString().c_str(), sizeof(m_param.curValue));
    memcpy(m_param.min, doc_element.attribute("min", "0").toStdString().c_str(), sizeof(m_param.min));
    memcpy(m_param.max, doc_element.attribute("max", "0").toStdString().c_str(), sizeof(m_param.max));

//    param.paramID = doc_element.attribute("paramID");
//    param.widgetType = doc_element.attribute("widgetType");
//    param.dataType = doc_element.attribute("dataType");
//    param.inputProperty = doc_element.attribute("inputProperty");
//    param.label = doc_element.attribute("label");
//    param.coefficient = doc_element.attribute("coefficient");
//    param.decimal = doc_element.attribute("decimal");
//    param.defaultValue = doc_element.attribute("defaultValue");
//    param.curValue = param.defaultValue;
//    param.min = doc_element.attribute("min");
//    param.max = doc_element.attribute("max");

    setRange(m_min, m_max);
    setSingleStep(m_coefficient);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    // 设置参数默认值
    QVariant var;
    var.setValue(m_param);
    setParamVaule(var);
}

QVariant IntegerSpinBox::paramVaule() const
{
//    paramItem.curValue = QString::number(value());
    memcpy((void *)m_param.curValue, QString::number(value()).toStdString().c_str(), sizeof(m_param.curValue));
    QVariant var;
    var.setValue(m_param);
    return var;
}

void IntegerSpinBox::setParamVaule(const QVariant &param_vaule)
{
    ParamItem paramItem = param_vaule.value<ParamItem>();
    memcpy(m_param.curValue, paramItem.curValue, sizeof(m_param.curValue));
    //setValue(paramItem.curValue.toInt());
    setValue(QString::fromUtf8(paramItem.curValue).toInt());
}

bool IntegerSpinBox::editMode() const
{
    return !isReadOnly();
}

void IntegerSpinBox::setEditMode(const bool editmode)
{
    setReadOnly(!editmode);
}

QString IntegerSpinBox::textFromValue(int value) const
{
    return QString::number(value);
}

int IntegerSpinBox::valueFromText(const QString &text) const
{
    return text.toInt();
}

QValidator::State IntegerSpinBox::validate(QString &text, int &pos) const
{
    QIntValidator validator(m_min, m_max);
    return validator.validate(text, pos);
}
