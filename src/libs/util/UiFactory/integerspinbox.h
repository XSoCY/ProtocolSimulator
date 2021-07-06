#ifndef INTEGERSPINBOX_H
#define INTEGERSPINBOX_H

#include <QDomElement>
#include <QSpinBox>
#include <QVariant>
#include "ConfigParamDefine.h"

/**
 * @brief The IntegerSpinBox class
 *

<Widget paramID="3_2" type="IntegerSpinBox" inputProperty="paramVaule" label="左旋手动加权系数"
    DecimalBase="255" decimal="4" min="0" max="255"/>

 */

class IntegerSpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule NOTIFY currentDataChanged)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    IntegerSpinBox(const QDomElement &doc_element, QWidget *parent = nullptr);
    ~IntegerSpinBox() {}

    QVariant paramVaule() const;
    void setParamVaule(const QVariant &param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

signals:
    void currentDataChanged(const QVariant& param_vaule);

protected:
    /**
     * @brief textFromValue 获取选值框文本来自于整型
     * @param value 整型值
     * @return
     */
    QString textFromValue(int value) const;
    /**
     * @brief textFromValue 获取选值框文本来自于字符串
     * @param text 字符串
     * @return
     */
    int valueFromText(const QString &text) const;

    QValidator::State validate(QString &text, int &pos) const;

private:
    int m_init_value;       //初始化值
    double m_coefficient;   //系数（步长）
    int m_min;              //最小值
    int m_max;              //最大值
    ParamItem m_param;       //参数结构体对应变量
};

#endif  // INTEGERSPINBOX_H
