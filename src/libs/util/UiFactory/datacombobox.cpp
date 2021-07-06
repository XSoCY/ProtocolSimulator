#include "datacombobox.h"
#include <QEvent>
#include <QDebug>
#include "uifactory.h"

Q_DECLARE_METATYPE(ParamItem)

DataComboBox::DataComboBox(const QDomElement& doc_element, QWidget* parent) : QComboBox(parent)
{
    if(doc_element.isNull())
    {
        return ;
    }
    m_edit_mode = false;
    m_init_value = doc_element.attribute("defaultValue", "0");
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

    QDomNode docNode = doc_element.firstChild();
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString strTagName = sub_doc_element.tagName();
            if (strTagName == "Item") {
                QString label = sub_doc_element.attribute("label");
                QString data  = sub_doc_element.attribute("data");
                addItem(label, QVariant(data));
            }
        }
        docNode = docNode.nextSibling();
    }

    installEventFilter(this);
    QVariant var;
    var.setValue(m_param);
    setParamVaule(var);
    connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            [=](int index) {
        emit currentDataChanged(paramVaule());
    });
}

QVariant DataComboBox::paramVaule() const
{
    memcpy((void *)m_param.curValue, currentData().toString().toStdString().c_str(), sizeof(m_param.curValue));
    QVariant var;
    var.setValue(m_param);
    return var;
}

void DataComboBox::setParamVaule(const QVariant& param_vaule)
{
    ParamItem paramItem = param_vaule.value<ParamItem>();
    int index = findData(QVariant(QString::fromUtf8(paramItem.curValue)));
    if (index == -1)
    {
        return;
    }
    memcpy(m_param.curValue, paramItem.curValue, sizeof(m_param.curValue));
    setCurrentIndex(index);
}

bool DataComboBox::editMode() const
{
    return m_edit_mode;
}

void DataComboBox::setEditMode(bool edit_mode)
{
    m_edit_mode = edit_mode;
}

bool DataComboBox::eventFilter(QObject *obj, QEvent *event)
{
    if (m_edit_mode){
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
