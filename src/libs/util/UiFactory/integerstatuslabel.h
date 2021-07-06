#ifndef INTEGERSTATUSLABEL_H
#define INTEGERSTATUSLABEL_H

#include "bitstatuslabel.h"
#include <QDomElement>
#include <QLabel>
#include <QTimer>

/**
 * @brief The IntegerStatusLabel class

<Widget paramID="3" type="IntegerStatusLabel" inputProperty="paramVaule" label="调制器状态" normalValue="1"
abnormalValue="2"/>

 */

class IntegerStatusLabel : public StatusLabel
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit IntegerStatusLabel(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return false;
    }

    void setEditMode(const bool editmode) {}

private:
    quint64 normal_value_   = 1;
    quint64 abnormal_value_ = 2;
};

#endif  // INTEGERSTATUSLABEL_H
