#include "doublespinbox.h"
#include "uifactory.h"

Q_DECLARE_METATYPE(ParamItem)

DoubleSpinBox::DoubleSpinBox(const QDomElement &doc_element, QWidget *parent) : QDoubleSpinBox(parent)
{
    m_decimal = doc_element.attribute("decimal").toInt();
    m_coefficient = doc_element.attribute("coefficient", "1").toDouble();
    m_init_value = doc_element.attribute("defaultValue", "0").toDouble();
    m_min = doc_element.attribute("min").toDouble();
    m_max = doc_element.attribute("max").toDouble();
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

    setRange(m_min, m_max);
    setDecimals(m_decimal);
    setSingleStep(m_coefficient);
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(setValue(double)));
    // 设置参数默认值
    QVariant var;
    var.setValue(m_param);
    setParamVaule(var);
}

QVariant DoubleSpinBox::paramVaule() const
{
    memcpy((void *)m_param.curValue, QString::number(value(), 'g', m_decimal).toStdString().c_str(), sizeof(m_param.curValue));
    QVariant var;
    var.setValue(m_param);
    return var;
}

void DoubleSpinBox::setParamVaule(const QVariant &param_vaule)
{
    ParamItem paramItem = param_vaule.value<ParamItem>();
    memcpy(m_param.curValue, paramItem.curValue, sizeof(m_param.curValue));
    setValue(QString::fromUtf8(paramItem.curValue).toDouble());
}

bool DoubleSpinBox::editMode() const
{
    return !isReadOnly();
}

void DoubleSpinBox::setEditMode(const bool editmode)
{
    setReadOnly(!editmode);
}

/**
 * @brief textFromValue 获取选值框文本来自于浮点
 * @param value 浮点型值
 * @return
 */
QString DoubleSpinBox::textFromValue(double value) const
{
    return QString::number(value, 'g', m_decimal);
}
/**
 * @brief textFromValue 获取选值框浮点型数据来自于字符串
 * @param text 字符串
 * @return
 */
double DoubleSpinBox::valueFromText(const QString &text) const
{
    return text.toDouble();
}

QValidator::State DoubleSpinBox::validate(QString &text, int &pos) const
{
    QDoubleValidator validator(m_min, m_max, m_decimal);
    return validator.validate(text, pos);
}
