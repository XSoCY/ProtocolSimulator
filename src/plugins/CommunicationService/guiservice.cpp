#include "guiservice.h"
#include "udpchannel.h"
#include "commchannel.h"
#include "communication_define.h"
#include "communication_equipment.h"
#include <QDebug>
#include "mainwindow.h"
#include "sqltableform.h"
GuiService::GuiService(BundleContext context):m_context(context)
{

}

GuiService::~GuiService()
{

}

QWidget *GuiService::CreateGui()
{

    m_widget = new MainWindow(m_context);
    return m_widget;
}

void GuiService::SendMessge(QByteArray byte, QString chnnaID)
{
    m_widget->sendData(byte,chnnaID);
}

