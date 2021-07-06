#ifndef INTEGERDOUBLESPINBOX_H
#define INTEGERDOUBLESPINBOX_H

#include <QDomElement>
#include <QDoubleSpinBox>

/**
 * @brief The IntegerDoubleSpinBox class

<Widget paramID="103" type="IntegerDoubleSpinBox" inputProperty="paramVaule" label="下行频率（MHz）"
coefficient="0.000001" decimal="6" min="0" max="99999999"/>

 */

class IntegerDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit IntegerDoubleSpinBox(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return !isReadOnly();
    }
    void setEditMode(const bool editmode)
    {
        setReadOnly(!editmode);
    }

private:
    double coefficient_ = 0;
};

#endif  // INTEGERDOUBLESPINBOX_H
