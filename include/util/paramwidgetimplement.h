#ifndef PARAMWIDGETIMPLEMENT_H
#define PARAMWIDGETIMPLEMENT_H

#include <QDomElement>
#include <QMultiMap>
#include <QVariant>
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include "util_global.h"
#include "ConfigParamDefine.h"

class UiFactory;

class UTILSHARED_SELF_EXPORT IParamWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode
    {
        StatusMode,
        EditMode
    };
    IParamWidget(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~IParamWidget() {}

    virtual void setValue(const QMap<QString, QVariant> &param_id_to_value) = 0;
    virtual QMap<QString, QVariant> getSettingValue() const                 = 0;

    virtual void setComparedValue(const QMap<QString, QVariant> &param_id_to_value) = 0;

    virtual void setMode(Mode mode) = 0;
    virtual Mode mode() const       = 0;
};

class UTILSHARED_SELF_EXPORT ParamWidgetImplement : public IParamWidget
{
    Q_OBJECT
public:
    /**
     * @brief ParamWidgetImplement 参数窗口部件构造函数
     * @param ucType    0：参数设置 1：参数宏
     * @param ui_xml    UI配置节点
     * @param relation_xml  关联配置节点 暂不使用（只用一个配置文件配置）
     * @param parent
     */
    ParamWidgetImplement(const QDomElement &ui_xml,
                         const QDomElement &relation_xml = QDomElement(),
                         const uchar ucType = -1,
                         QWidget *parent                 = nullptr);
    virtual ~ParamWidgetImplement();

    /**
     * @brief setValue          设置所有参数值QMap<参数ID，参数值>
     */
    virtual void setValue(const QMap<QString, QVariant> &param_id_to_value);

    /**
     * @brief getSettingValue   获得所有设置参数值QMap<参数ID，参数值>
     * @return
     */
    virtual QMap<QString, QVariant> getSettingValue() const;

    virtual void setComparedValue(const QMap<QString, QVariant> &param_id_to_value);

    /**
     * @brief setMode       设置窗口编辑模式
     * @param mode      true：可编辑 false：不可编辑
     */
    virtual void setMode(Mode mode);
    /**
     * @brief mode       获得窗口编辑模式
     * @return true：可编辑 false：不可编辑
     */
    virtual Mode mode() const;

signals:
    /**
     * @brief signal_ParamSend  参数下发信号
     */
    void signal_ParamSet(void);

protected slots:

    /**
     * @brief slot_EditButtonClicked    编辑参数按钮点击槽
     */
    void slot_EditButtonClicked(bool);

    /**
     * @brief slot_SetButtonClicked     参数设置按钮点击槽
     */
    void slot_SetButtonClicked(bool);

private:
    QWidget *m_pWidget = nullptr;

    QPushButton *m_edit_button = nullptr;

    QPushButton *m_set_button = nullptr;

    //编辑前参数值QMap<参数ID，参数值>
    QMap<QString, QVariant> m_prev_edit_value;
};

#endif  // PARAMWIDGETIMPLEMENT_H
