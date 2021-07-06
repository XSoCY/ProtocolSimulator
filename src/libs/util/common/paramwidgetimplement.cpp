#include "paramwidgetimplement.h"
#include "uifactory.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

Q_DECLARE_METATYPE(ParamItem)

/**
 * @brief ParamWidgetImplement 参数窗口部件构造函数
 * @param ucType    0：参数设置 1：参数宏
 * @param ui_xml    UI配置节点
 * @param relation_xml  关联配置节点 暂不使用（只用一个配置文件配置）
 * @param parent
 */
ParamWidgetImplement::ParamWidgetImplement(const QDomElement &ui_xml,
                                           const QDomElement &relation_xml, const uchar ucType,
                                           QWidget *parent)
    : IParamWidget(parent)
{
    m_pWidget = UiFactory::instance().createProduct("LayoutWidget", ui_xml, relation_xml);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_pWidget);
    if (m_pWidget) {
        // 参数设置
        if(ucType == 0)
        {
            m_edit_button = new QPushButton("参数修改");
            m_set_button = new QPushButton("参数下发");
            m_edit_button->setEnabled(true);
            m_set_button->setEnabled(false);
            // 参数修改
            connect(m_edit_button, SIGNAL(clicked(bool)), this, SLOT(slot_EditButtonClicked(bool)));
            // 参数下发
            connect(m_set_button, SIGNAL(clicked(bool)), this, SLOT(slot_SetButtonClicked(bool)));
            auto h_layout = new QHBoxLayout;
            h_layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
            h_layout->addWidget(m_edit_button);
            h_layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));
            h_layout->addWidget(m_set_button);
            h_layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
            layout->addLayout(h_layout);
        }
        // 参数宏
        else if(ucType == 1)
        {
            // 参数宏可编辑
            m_pWidget->setProperty("editMode", true);
        }
        //参数状态界面
        else
        {
            // 参数状态不可编辑
            m_pWidget->setProperty("editMode", false);
        }
    }
    setLayout(layout);
}

ParamWidgetImplement::~ParamWidgetImplement() {}

/**
 * @brief setValue   设置所有参数值QMap<参数ID，参数值>
 */
void ParamWidgetImplement::setValue(const QMap<QString, QVariant> &param_id_to_value)
{
    if (m_pWidget) {
        m_pWidget->setProperty("paramVaule", param_id_to_value);
    }
}

/**
 * @brief getSettingValue   获得所有设置参数值QMap<参数ID，参数值>
 * @return
 */
QMap<QString, QVariant> ParamWidgetImplement::getSettingValue() const
{
    if (m_pWidget) {
        auto variant = m_pWidget->property("paramVaule");
        if (variant.canConvert<QMap<QString, QVariant>>()) {
            return variant.toMap();
        }
    }
    return QMap<QString, QVariant>();
}

void ParamWidgetImplement::setComparedValue(const QMap<QString, QVariant> &param_id_to_value)
{
    if (m_pWidget) {
        m_pWidget->setProperty("comparedValue", param_id_to_value);
    }
}

/**
 * @brief setMode       设置窗口编辑模式
 * @param mode      true：可编辑 false：不可编辑
 */
void ParamWidgetImplement::setMode(IParamWidget::Mode mode)
{
    if (m_pWidget) {
        m_pWidget->setProperty("editMode", mode == EditMode);
    }
}

/**
 * @brief mode       获得窗口编辑模式
 * @return true：可编辑 false：不可编辑
 */
IParamWidget::Mode ParamWidgetImplement::mode() const
{
    if (m_pWidget) {
        return (m_pWidget->property("editMode").toBool()) ? EditMode : StatusMode;
    }
    return StatusMode;
}


/**
 * @brief slot_EditButtonClicked    编辑参数按钮点击槽
 */
void ParamWidgetImplement::slot_EditButtonClicked(bool)
{
    // 编辑模式退出
    if (m_pWidget->property("editMode").toBool() == true) {
        if (QMessageBox::question(nullptr,
                                  QString("提示"),
                                  QString("是否退出修改模式？"),
                                  QString("是"),
                                  QString("否"))
            == 0) {
            // 重置参数
            setValue(m_prev_edit_value);
            // 打印参数
            for(int i = 0; i < m_prev_edit_value.size(); i++)
            {
                QString paramID = m_prev_edit_value.keys().at(i);
                qDebug() << QString("重置参数[%1],值[%2]").arg(paramID).arg(m_prev_edit_value[paramID].value<ParamItem>().curValue);
            }
            m_pWidget->setProperty("editMode", false);
            m_edit_button->setEnabled(true);
            m_edit_button->setText(QString("参数修改"));
            m_set_button->setEnabled(false);
            return;
        }
    }
    // 进入编辑模式
    else if (m_pWidget->property("editMode").toBool() == false) {
        // 获得当前参数值
        m_prev_edit_value = getSettingValue();
        m_pWidget->setProperty("editMode", true);
        m_edit_button->setEnabled(true);
        m_edit_button->setText("退出修改");
        m_set_button->setEnabled(true);
    }
}

/**
 * @brief slot_SetButtonClicked     参数设置按钮点击槽
 */
void ParamWidgetImplement::slot_SetButtonClicked(bool)
{
    // 获得设置参数值列表
    QMap<QString, QVariant> paramlist = getSettingValue();
    //参数校验
    if (paramlist.isEmpty()) {
        QMessageBox::warning(nullptr, QString("警告"), QString("下发参数为空."), QString("确定"));
        return;
    }
    else {
        QMessageBox::warning(nullptr, QString("警告"), QString("参数设置不合法."), QString("确定"));
    }
    // 写日志

    // 发送参数设置命令
    emit signal_ParamSet();
}
