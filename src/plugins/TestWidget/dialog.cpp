#include "dialog.h"
#include "cppmicroservices/Bundle.h"
#include "cppmicroservices/GetBundleContext.h"
#include "ui_dialog.h"
#include <QDebug>
#include "ICommunicationService.h"
using namespace cppmicroservices;

Dialog::Dialog(BundleContext context, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    m_context = context;
    // Q_UNUSED(context)
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    auto service = m_context.GetService<ICommunicationServiceInterface>();

    char test = 0x35;
    QByteArray data(&test, sizeof(test));
    qDebug() << "send start:" << data.toHex();
    if( service )
        service->sendMessage("htsy", data, ui->lineEdit->text());
}
