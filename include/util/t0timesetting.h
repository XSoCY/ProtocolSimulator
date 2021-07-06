#ifndef T0TIMESETTING_H
#define T0TIMESETTING_H

#include <QDomElement>
#include <QVariant>
#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

/**
 * @brief The T0TimeSetting class

<Widget paramID="101" type="T0TimeSetting" inputProperty="paramVaule" label="T0时刻"/>

 */

class T0TimeSetting : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit T0TimeSetting(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

private:
    bool edit_mode_ = false;

    QSpinBox*       day_    = nullptr;
    QSpinBox*       hour_   = nullptr;
    QSpinBox*       min_    = nullptr;
    QDoubleSpinBox* second_ = nullptr;
};

#endif  // T0TIMESETTING_H
