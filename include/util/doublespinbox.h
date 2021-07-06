#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QDomElement>
#include <QDoubleSpinBox>
#include <QVariant>
#include "ConfigParamDefine.h"

class DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule NOTIFY currentDataChanged)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit DoubleSpinBox(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

signals:
    void currentDataChanged(const QVariant& param_vaule);

protected:
    /**
     * @brief textFromValue 获取选值框文本来自于浮点
     * @param value 浮点型值
     * @return
     */
    QString textFromValue(double value) const;
    /**
     * @brief textFromValue 获取选值框浮点型数据来自于字符串
     * @param text 字符串
     * @return
     */
    double valueFromText(const QString &text) const;

    QValidator::State validate(QString &text, int &pos) const;
private:

    int m_decimal;             //保留小数位数
    double m_init_value;       //初始化值
    double m_coefficient;      //系数（步长）
    double m_min;              //最小值
    double m_max;              //最大值
    ParamItem m_param;       //参数结构体对应变量
};

#endif // DOUBLESPINBOX_H
