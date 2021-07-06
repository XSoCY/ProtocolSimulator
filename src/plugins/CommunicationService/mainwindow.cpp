#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqltableform.h"
#include "ttccombinationform.h"
#include "communication_define.h"
#include "ttcfrontcomputerform.h"
MainWindow::MainWindow(BundleContext context,QWidget *parent) :
    QMainWindow(parent),m_context(context),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SQLTableForm = new SQLTableForm(m_context);
    m_TTCcombinationForm = new TTCcombinationForm(m_context);
    m_TTCFrontComputerForm = new TTCFrontComputerForm(m_context);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendData(QByteArray byte, QString chnnaID)
{
    if(chnnaID == CHANNEL_ID_Equipment)
    {
        m_SQLTableForm->slot_recv(byte);
    }
    else if(chnnaID == CHANNEL_ID_TTCCombination)
    {
        m_TTCcombinationForm->slot_recv(byte);
    }
    else if(chnnaID == CHANNEL_ID_TTCFrontCompter)
    {
        m_TTCFrontComputerForm->slot_recv(byte);
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_SQLTableForm->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    m_TTCcombinationForm->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    m_TTCFrontComputerForm->show();
}
