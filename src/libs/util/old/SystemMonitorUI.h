#ifndef SYSTEMMONITORUI_H
#define SYSTEMMONITORUI_H

#include "Common/DeviceButton.h"
#include "Paramacro/CreateParaMacroWidget.h"
#include "Paramacro/ParameterMacroListWidget.h"
#include "Paramacro/parametermacrowidget.h"
#include "SystemAlert/systemalertview.h"
#include "SystemState/systemstate.h"
#include "Unit/UnitInfoWidget.h"
#include <QButtonGroup>
#include <QWidget>

namespace Ui
{
class SystemMonitorUI;
}

class SystemMonitorUI : public QWidget
{
    Q_OBJECT

public:
    explicit SystemMonitorUI(QWidget* parent = 0);
    QSize sizeHint() const;
    ~SystemMonitorUI();

protected:
    void closeEvent(QCloseEvent* event);

public:
    void setText(const QString& strTitle);
    void initUI();

private slots:
    void on_btnMonitor_clicked();
    void on_btnParamMacro_clicked();

    void on_btnsystemstate_clicked();
    void on_btnalert_clicked();
    void on_btnsysblock_clicked();

    //设备按钮点击事件
    void on_DeviceBtn_clicked(int sysID, int devID, int extID, int modeID);

private:
    void initTopBtns();
    void initStackedWidget();
    void initFileInfo();
    void initAutoRunInfo();
    void initLogInfo();

    //获取设备按钮
    void GetDeviceButtons();
    void paintEvent(QPaintEvent* event);

private:
    Ui::SystemMonitorUI* ui;
    QString m_strTitle;
    QWidget* m_pParent;

    QButtonGroup* m_switchButtons;
    UnitInfoWidget* m_uiw;
    ParameterMacroListWidget* m_pmlw;
    SystemState* m_systemState;
    SystemAlertView* m_systemAlert;

    QList<DeviceButton*> m_deviceBtnList;  //设备按钮列表

    ICurrentState* m_currentState;
    IGlobalData* m_globalData;
};

#endif  // SYSTEMMONITORUI_H
