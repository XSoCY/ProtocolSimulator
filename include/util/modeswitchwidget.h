#ifndef MODESWITCHWIDGET_H
#define MODESWITCHWIDGET_H

#include <QDomElement>
#include <QMap>
#include <QVariant>
#include <QWidget>

class QComboBox;

class ModeSwitchWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    ModeSwitchWidget(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

private:
    void initUI(const QDomElement& doc_element);

private:
    QComboBox* combobox_ = nullptr;

    QMap<unsigned int, QWidget*> mode_head_value_to_widget_;
};

#endif  // MODESWITCHWIDGET_H
