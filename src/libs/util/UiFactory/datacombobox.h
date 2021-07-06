#ifndef DATACOMBOBOX_H
#define DATACOMBOBOX_H

#include <QComboBox>
#include <QDomElement>
#include <QVariant>
#include "ConfigParamDefine.h"

/**
 * @brief The DataComboBox class

 <Widget paramID="2" type="DataComboBox" inputProperty="paramVaule" label="测角采样率">
    <Item label="无此参数" data="0"/>
    <Item label="1次/秒" data="1"/>
    <Item label="4次/秒" data="2"/>
    <Item label="10次/秒" data="3"/>
    <Item label="20次/秒" data="4"/>
    <Item label="0.2次/秒" data="5"/>
    <Item label="2次/秒" data="6"/>
 </Widget>

 */
class ParamItem;

class DataComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule NOTIFY currentDataChanged)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit DataComboBox(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(bool edit_mode);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void currentDataChanged(const QVariant& param_vaule);

private:
    bool m_edit_mode;   // 编辑模式 true：可编辑    false：不可编辑
    bool first_setting_ = false;

    QString m_init_value;   // 初始化值
    ParamItem m_param;       //参数结构体对应变量
};

#endif  // DATACOMBOBOX_H
