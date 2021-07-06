#ifndef BITCOMBOBOX_H
#define BITCOMBOBOX_H

#include <QComboBox>
#include <QDomElement>
#include <QWidget>

class BitCombobox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule NOTIFY currentDataChanged)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    BitCombobox(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(bool edit_mode);

    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void currentDataChanged(const QVariant& param_vaule);

private:
    bool edit_mode_     = false;
    bool first_setting_ = false;

    int value_start_bit_ = 0;
    int value_bit_len_   = 0;
};

#endif  // BITCOMBOBOX_H
