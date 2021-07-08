#include "ttcfrontcomputerform.h"
#include "ui_ttcfrontcomputerform.h"
#include "ICommunicationService.h"
#include "communication_define.h"
#include "CommonDefine/commonprotocolstruct.h"
#include "worker.h"
#include <QDebug>
TTCFrontComputerForm::TTCFrontComputerForm(BundleContext context,QWidget *parent) :
    QWidget(parent),m_context(context),
    ui(new Ui::TTCFrontComputerForm)
{
    ui->setupUi(this);
    setWindowTitle("测发控前端计算机");
    initThread();
}

TTCFrontComputerForm::~TTCFrontComputerForm()
{
    delete ui;
}

void TTCFrontComputerForm::slot_recv(const QByteArray byte)
{
    QString dataStr(byte.toHex().toUpper());
    QString displayStr;
    for(int i=0, cnt=dataStr.size(); i < cnt; i++) {
        if(i%2 == 0 && i != 0) {
            displayStr += ' ';
        }
        displayStr += dataStr.at(i);
    }
    ui->labelRecv->setText(displayStr);

    qDebug()<<"TTCFrontComputerForm: "<<byte.data();
}

void TTCFrontComputerForm::closeEvent(QCloseEvent *event)
{
    this->hide();
}

void TTCFrontComputerForm::on_pBtnSend_clicked()
{
    QByteArray datas;
    packBaseFrame(datas);
    packData(datas);
    unsigned char initvalue = 0;
    unsigned char sum = std::accumulate(datas.begin(), datas.end(),initvalue);
    datas.append(sum);
    sendData(datas);
}

void TTCFrontComputerForm::packData(QByteArray &data)
{
    QDataStream dataStream(&data, QIODevice::Append);
    dataStream.setByteOrder(QDataStream::LittleEndian);	//统一设置为小端模式
    dataStream.setVersion(QDataStream::Qt_4_5);//设置为前期版本，float为32位，double为64位，Qt_4_6以后版本两者长度统一
    bool ok;
    dataStream << (quint8)ui->lineEditNum_1->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_2->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_3->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_4->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_5->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_6->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_7->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_8->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_9->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_10->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_11->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_12->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_13->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_14->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_15->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_16->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_17->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_18->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_19->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_20->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_21->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_22->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_23->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_24->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_25->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_26->text().toUInt(&ok, 16);
    dataStream << (quint8)ui->lineEditNum_27->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_28->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_29->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_30->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_31->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_32->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_33->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_34->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_35->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_36->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_37->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_38->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_39->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_40->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_41->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_42->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_43->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_44->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_45->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditNum_46->text().toUInt(&ok, 16);
}

void TTCFrontComputerForm::packBaseFrame(QByteArray &data)
{
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::LittleEndian);	//统一设置为小端模式
    dataStream.setVersion(QDataStream::Qt_4_5);//设置为前期版本，float为32位，double为64位，Qt_4_6以后版本两者长度统一
    //1,获取基本协议头
    BaseFram_t mBaseFram;
    mBaseFram.head          = 0x4E4A;   //固定值
    mBaseFram.dataLength    = 76;      //数据域固定155Byte
    mBaseFram.SID           = TLC_FRONT_END;
    mBaseFram.DID           = SERVER;
    mBaseFram.type          = UpType;
    dataStream << mBaseFram;
}

int TTCFrontComputerForm::sendData(const QByteArray &data)
{
    auto serviceRef = m_context.GetServiceReference<ICommunicationServiceInterface>();

    std::shared_ptr<ICommunicationServiceInterface> com_service =
        m_context.GetService<ICommunicationServiceInterface>(serviceRef);
    if (com_service.get())
    {
       return com_service->sendMessage(CHANNEL_ID_TTCFrontCompter, data);
    }
    else {
        qDebug() << "Get communicationService failed!";
        return 0;
    }
}

void TTCFrontComputerForm::initThread()
{
    Worker *worker = new Worker;
    worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &TTCFrontComputerForm::startAutoSend, worker, &Worker::startAutoSend);
    connect(this, &TTCFrontComputerForm::stopAutoSend, worker, &Worker::stopAutoSend);
    connect(worker, &Worker::sendData, this, &TTCFrontComputerForm::on_pBtnSend_clicked, Qt::DirectConnection);
    m_workerThread.start();
}

void TTCFrontComputerForm::on_pBtnClear_clicked()
{
    ui->labelRecv->clear();
}

void TTCFrontComputerForm::on_checkBox_send_clicked(bool checked)
{
    if(checked) {
        emit startAutoSend(ui->spinBox->value());
    } else {
        emit stopAutoSend();
    }
}

void TTCFrontComputerForm::on_spinBox_valueChanged(int arg1)
{
    if(ui->checkBox_send->isChecked()) {
        emit startAutoSend(arg1);
    }
}
