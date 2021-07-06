#ifndef SPECIALNAGATIVEDOUBLESPINBOX_H
#define SPECIALNAGATIVEDOUBLESPINBOX_H

#include <QDomElement>
#include <QDoubleSpinBox>

class SpecialNagativeDoubleSpinbox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit SpecialNagativeDoubleSpinbox(const QDomElement& doc_element, QWidget* parent = nullptr);

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
    double coefficient_  = 0;
    int    nagetive_bit_ = 0;
};

#endif  // SPECIALNAGATIVEDOUBLESPINBOX_H
