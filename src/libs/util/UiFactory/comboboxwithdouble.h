#ifndef COMBOBOXWITHDOUBLE_H
#define COMBOBOXWITHDOUBLE_H

#include <QComboBox>
#include <QDomElement>
#include <QWidget>

class ComboboxWithDouble : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule NOTIFY currentDataChanged)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    ComboboxWithDouble(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(bool edit_mode);

    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void currentDataChanged(const QVariant& param_vaule);

private:
    void initUI();
    void initXml(const QDomElement& doc_element);
    void initWidget(const QDomElement& doc_element, QComboBox* combobox);

private:
    bool edit_mode_     = false;
    bool first_setting_ = false;

    QComboBox* main_widget_ = nullptr;
    QComboBox* sub_widget_  = nullptr;
};

#endif  // COMBOBOXWITHDOUBLE_H
