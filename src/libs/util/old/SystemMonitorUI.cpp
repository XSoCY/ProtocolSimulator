#include "SystemMonitorUI.h"
#include "AutoRun/autoruninfo.h"
#include "FileInfo/fileinfoitemmodel.h"
#include "ICurrentState.h"
#include "IGlobalData.h"
#include "LogInfo/loginfoitemmodel.h"
#include "Util/uiutil.h"
#include "ui_SystemMonitorUI.h"
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QPainter>

SystemMonitorUI::SystemMonitorUI(QWidget* parent) : QWidget(parent), ui(new Ui::SystemMonitorUI)
{
    m_pParent = parent;
    m_switchButtons = new QButtonGroup(this);
    m_uiw = NULL;
    m_pmlw = NULL;
    m_systemState = NULL;
    m_systemAlert = NULL;
    m_currentState = getCurrentStateInterface();
    m_globalData = getGlobalDataInterface();

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::FramelessWindowHint);
    initUI();
}

SystemMonitorUI::~SystemMonitorUI()
{
    delete ui;
}

void SystemMonitorUI::setText(const QString& strTitle)
{
    m_strTitle = strTitle;
    setWindowTitle(strTitle);
}

void SystemMonitorUI::initUI()
{
    initTopBtns();
    initStackedWidget();
    initFileInfo();
    initAutoRunInfo();
    initLogInfo();
    UiUtil::getInstance()->loadQss();
}

QSize SystemMonitorUI::sizeHint() const
{
    return QSize(this->width(), this->height());
}

void SystemMonitorUI::closeEvent(QCloseEvent* event)
{
    event->accept();
    m_pParent->close();
}

void SystemMonitorUI::on_btnMonitor_clicked()
{
    const int sysID = 0x04;  // CurrentState::instance().currentSystemID();
    const int devID = 0x0;   // CurrentState::instance().currentDeviceID();
    const int extID = 0x1;   // CurrentState::instance().currentExtensionID();

    ICurrentState* currentState = getCurrentStateInterface();
    currentState->setCurrentSystemID(sysID);
    currentState->setCurrentDeviceID(devID);
    currentState->setCurrentExtensionID(extID);

    Extension ext;
    currentState->extension(sysID, devID, extID, ext);
    qDebug() << "=> " << sysID << " " << devID << " " << extID << ext.ModeCtrlMap.keys();
    if (!ext.ModeCtrlMap.isEmpty())
    {
        currentState->setCurrentModeID(ext.ModeCtrlMap.first().ID);
        qDebug() << "ext.ModeCtrlMap.first().ID = " << ext.ModeCtrlMap.firstKey();
    }

    const int modeID = 1;  // CurrentState::instance().currentModeID();
    const QMap<int, Unit> units = currentState->units(sysID, devID, extID, modeID);

    if (units.isEmpty())
    {
        // QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("没有找到单元信息!"));
        // return;
    }

    IGlobalData* globalData = getGlobalDataInterface();
    QMap<int, System> systemMap = globalData->getSystemMap();
    if (!systemMap.contains(sysID))
    {
        return;
    }
    System& sys = systemMap[sysID];

    if (!sys.deviceMap.contains(devID))  //
    {
        return;
    }
    Device& dev = sys.deviceMap[devID];

    if (!dev.extensionMap.contains(extID))  //
    {
        return;
    }
    Extension& currentExten = dev.extensionMap[extID];
    if (!currentExten.ModeCtrlMap.contains(modeID))  //
    {
        return;
    }
    currentExten.currentModeID = modeID;
    m_uiw->initWithUnits(units);
    ui->stackedWidget->setCurrentWidget(m_uiw);
}

void SystemMonitorUI::on_btnParamMacro_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_pmlw);
}
void SystemMonitorUI::on_btnsystemstate_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_systemState);
}

void SystemMonitorUI::on_btnalert_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_systemAlert);
}

void SystemMonitorUI::on_btnsysblock_clicked() {}

void SystemMonitorUI::on_DeviceBtn_clicked(int sysID, int devID, int extID, int modeID)
{
    if (NULL = m_currentState || NULL = m_globalData)
    {
        return;
    }

    const int iSysID = sysID;
    const int iDevID = devID;
    const int iExtID = extID;
    const int iModeID = modeID;

    m_currentState->setCurrentSystemID(iSysID);
    m_currentState->setCurrentDeviceID(iDevID);
    m_currentState->setCurrentExtensionID(iExtID);
    m_currentState->setCurrentModeID(iModeID);

    QMap<int, System> systemMap = m_globalData->getSystemMap();
    if (!systemMap.contains(sysID))
    {
        return;
    }
    System& sys = systemMap[sysID];

    if (!sys.deviceMap.contains(devID))  //
    {
        return;
    }
    Device& dev = sys.deviceMap[devID];

    if (!dev.extensionMap.contains(extID))  //
    {
        return;
    }
    Extension& currentExten = dev.extensionMap[extID];
    if (!currentExten.ModeCtrlMap.contains(modeID))  //
    {
        return;
    }
    currentExten.currentModeID = modeID;

    const QMap<int, Unit> units = m_currentState->units(sysID, devID, extID, modeID);
    m_uiw->initWithUnits(units);
    ui->stackedWidget->setCurrentWidget(m_uiw);
}

void SystemMonitorUI::initTopBtns()
{
    GetDeviceButtons();

    int index = ui->horizontalLayout->layout()->count() - 1;
    for (int i = 0; i < m_deviceBtnList.length(); i++)
    {
        ui->horizontalLayout->insertWidget(index + i, m_deviceBtnList.at(i));
        m_switchButtons->addButton(m_deviceBtnList.at(i));
    }

    m_switchButtons->addButton(ui->btnsystemstate);
    m_switchButtons->addButton(ui->btnalert);
    m_switchButtons->addButton(ui->btnsysblock);
    m_switchButtons->addButton(ui->btnMonitor);
    m_switchButtons->addButton(ui->btnParamMacro);

    foreach (QAbstractButton* btn, m_switchButtons->buttons())
    {
        btn->setProperty("class", "GroupItemButton");
    }
    connect(m_switchButtons, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), [this](QAbstractButton* button) {
        if (button == ui->btnsystemstate)
            on_btnsystemstate_clicked();
        if (button == ui->btnalert)
            on_btnalert_clicked();
        if (button == ui->btnsysblock)
            on_btnsysblock_clicked();
        if (button == ui->btnMonitor)
            on_btnMonitor_clicked();
        if (button == ui->btnParamMacro)
            on_btnParamMacro_clicked();
        for (int i = 0; i < m_deviceBtnList.length(); i++)
        {
            if (button == m_deviceBtnList.at(i))
            {
                int sysID = m_deviceBtnList.at(i)->GetSystemID();
                int devID = m_deviceBtnList.at(i)->GetDeviceID();
                int extID = m_deviceBtnList.at(i)->GetExtensionID();
                int modeID = m_deviceBtnList.at(i)->GetModeID();
                on_DeviceBtn_clicked(sysID, devID, extID, modeID);
            }
        }
    });
}

void SystemMonitorUI::GetDeviceButtons()
{
    if (NULL = m_currentState || NULL = m_globalData)
    {
        return;
    }

    QMap<int, System> systemMap = m_globalData->getSystemMap();
    if (systemMap.isEmpty())
    {
        return;
    }

    QMap<int, System>::const_iterator iterSys = systemMap.begin();
    for (; iterSys != systemMap.end(); iterSys++)
    {
        System sys = iterSys.value();
        QMap<int, Device> devMap = m_currentState->devices(sys.ID);
        if (devMap.isEmpty())
        {
            continue;
        }

        QMap<int, Device>::const_iterator iterDev = devMap.begin();
        for (; iterDev != devMap.end(); iterDev++)
        {
            Device dev = iterDev.value();
            QString deviceName = dev.desc;
            QMap<int, Extension> extMap = m_currentState->extensions(sys.ID, dev.ID);
            if (extMap.isEmpty())
            {
                continue;
            }

            QMap<int, Extension>::const_iterator iterExt = extMap.begin();
            for (; iterExt != extMap.end(); iterExt++)
            {
                Extension ext = iterExt.value();
                DeviceButton* devBtn = NULL;
                int modeID = 0xffff;
                if (ext.haveMode)
                {
                    if (!ext.ModeCtrlMap.isEmpty())
                    {
                        QMap<int, ModeCtrl>::const_iterator iterMode = ext.ModeCtrlMap.begin();
                        for (; iterMode != ext.ModeCtrlMap.end(); iterMode++)
                        {
                            modeID = iterMode.value().ID;
                            devBtn = new DeviceButton();
                            devBtn->InitButton(sys.ID, dev.ID, ext.ID, modeID, deviceName);
                            m_deviceBtnList.append(devBtn);
                        }
                    }
                    else
                    {
                        devBtn = new DeviceButton();
                        devBtn->InitButton(sys.ID, dev.ID, ext.ID, modeID, deviceName);
                        m_deviceBtnList.append(devBtn);
                    }
                }
                else
                {
                    devBtn = new DeviceButton();
                    devBtn->InitButton(sys.ID, dev.ID, ext.ID, modeID, deviceName);
                    m_deviceBtnList.append(devBtn);
                }
            }
        }
    }
}

void SystemMonitorUI::initStackedWidget()
{
    m_systemState = new SystemState();
    ui->stackedWidget->addWidget(m_systemState);
    ui->stackedWidget->setCurrentWidget(m_systemState);

    m_systemAlert = new SystemAlertView();
    ui->stackedWidget->addWidget(m_systemAlert);

    m_uiw = new UnitInfoWidget();
    ui->stackedWidget->addWidget(m_uiw);

    m_pmlw = new ParameterMacroListWidget();
    ui->stackedWidget->addWidget(m_pmlw);
}

void SystemMonitorUI::initFileInfo()
{
    ui->fileView->horizontalHeader()->setObjectName("fileHeaderView");

    // 设置单行选中、最后一列拉伸、表头不高亮、无边框等
    ui->fileView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->fileView->horizontalHeader()->setHighlightSections(false);
    ui->fileView->verticalHeader()->setVisible(false);
    ui->fileView->setShowGrid(false);
    ui->fileView->setFrameShape(QFrame::NoFrame);
    ui->fileView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->fileView->horizontalHeader()->setDefaultSectionSize(60);
    ui->fileView->verticalHeader()->setDefaultSectionSize(35);
    ui->fileView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    FileInfoItemModel* model = new FileInfoItemModel();
    ui->fileView->setModel(model);
    model->setColumnCount(3);
    model->setHeaderData(0, Qt::Horizontal, "类型");
    model->setHeaderData(1, Qt::Horizontal, "文件名称");
    model->setHeaderData(2, Qt::Horizontal, "文件大小");
}

void SystemMonitorUI::initAutoRunInfo()
{
    AutoRunInfo* autorun = new AutoRunInfo();
    ui->autorunlayout->addWidget(autorun);
}

void SystemMonitorUI::initLogInfo()
{
    ui->logView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    LogInfoItemModel* model = new LogInfoItemModel();
    ui->logView->setModel(model);
    model->setColumnCount(3);
    model->setHeaderData(0, Qt::Horizontal, "类型");
    model->setHeaderData(1, Qt::Horizontal, "时间");
    model->setHeaderData(2, Qt::Horizontal, "日志信息");
}

void SystemMonitorUI::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
