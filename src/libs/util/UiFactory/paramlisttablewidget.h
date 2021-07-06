#ifndef PARAMLISTTABLEWIDGET_H
#define PARAMLISTTABLEWIDGET_H

#include <QDebug>
#include <QDomElement>
#include <QTableWidget>

/**
 * @brief The ParamListTableWidget class

<Widget paramID="5" type="ParamListTableWidget" inputProperty="paramVaule" label="曲线表"
maxLoopSize="256"> <Widget paramID="1" type="IntegerDoubleSpinBox" inputProperty="paramVaule"
label="AGC" coefficient="1" decimal="0" min="0" max="99999999"/> <Widget paramID="2"
type="IntegerDoubleSpinBox" inputProperty="paramVaule" label="S/Φ" coefficient="1" decimal="0"
min="0" max="99999999"/>
</Widget>

 */

class QSpinBox;

class ParamListTableWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit ParamListTableWidget(const QDomElement &doc_element, QWidget *parent = nullptr);

    QVariant paramVaule() const;
    void setParamVaule(const QVariant &param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

private:
    void initUI(const QDomElement &doc_element);
    QWidget *createWidgetItem(const QDomElement &dom_element);

private:
    QMap<QPair<int, QString>, QPair<QWidget *, QString>>
        loop_index_sub_param_id_to_widget_input_property_name_;

    QSpinBox *loop_size_ = nullptr;
};

#endif  // PARAMLISTTABLEWIDGET_H
