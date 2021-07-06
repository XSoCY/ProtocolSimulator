#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QDomElement>
#include <QMultiMap>
#include <QVariant>
#include <QWidget>
#include <memory>
#include "util_global.h"
#include "ConfigParamDefine.h"

class IConditonProduct;
class IActionProduct;

class UTILSHARED_SELF_EXPORT LayoutWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)
    Q_PROPERTY(QVariant comparedValue READ comparedValue WRITE setComparedValue)

public:
    explicit LayoutWidget(const QDomElement &ui_xml,
                          const QDomElement &relation_xml,
                          QWidget *parent = nullptr);

    QVariant paramVaule() const;
    void setParamVaule(const QVariant &param_vaule);

    QVariant comparedValue() const;
    void setComparedValue(const QVariant &param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

    /**
     * @brief getAllParamWidgetProperty 获得所有参数输入部件属性QMap
     * @return
     */
    QMultiMap<QString, QPair<QWidget *, QString>> &getAllParamWidgetProperty()
    {
        return m_param_id_to_widget_input_property_name;
    }

protected:
    void showEvent(QShowEvent *event) override;

private:
    void initUI(const QDomElement &dom_element);
    void initRelation(const QDomElement &dom_element);
    QList<std::shared_ptr<IActionProduct>> initExcuteAction(const QDomElement &dom_element);

    void connectRelation(QWidget *widget, const QString &input_property_name);

    QWidget *createMultiWidgetItem(const QDomElement &dom_element);
    QWidget *createWidgetItem(const QDomElement &dom_element);
    QWidget *createGroupBox(const QDomElement &dom_element);
    QWidget *createGridLayout(const QDomElement &dom_element);
    QWidget *createHLayout(const QDomElement &dom_element);
    QWidget *createVLayout(const QDomElement &dom_element);

    void setValue(const QMap<QString, QVariant> &param_id_to_value);
    QMap<QString, QVariant> getSettingValue() const;

    Q_INVOKABLE void onWidgetPropertyChanged(const QVariant &value);

    void updateUI();

private:
    bool is_edit_mode_ = false;
    // 参数ID，参数ID对应的部件对象，动态属性名称
    QMultiMap<QString, QPair<QWidget *, QString>> m_param_id_to_widget_input_property_name;
    QMap<QWidget *, QString> widget_to_param_id_;
    QMap<QString, QWidget *> param_id_to_widget_;
    QMap<QString, QWidget *> param_id_to_label_;

    QMap<QString, QVariant> compared_value_;
    QMap<QString, QVariant> current_status_value_;

    // 参数ID，条件活动列表QMultiMap<参数ID，条件，活动键值对>
    QMultiMap<QString,
              QPair<std::shared_ptr<IConditonProduct>, QList<std::shared_ptr<IActionProduct>>>>
        param_id_to_condition_action_list;
};

#endif  // LAYOUTWIDGET_H
