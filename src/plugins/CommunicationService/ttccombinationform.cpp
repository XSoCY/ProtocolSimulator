#include "ttccombinationform.h"
#include "ui_ttccombinationform.h"
#include <QDebug>
#include "communication_define.h"
#include "ICommunicationService.h"
#include "CommonDefine/commonprotocolstruct.h"

TTCcombinationForm::TTCcombinationForm(BundleContext context,QWidget *parent) :
    QWidget(parent),m_context(context),
    ui(new Ui::TTCcombinationForm)
{
    ui->setupUi(this);
    setWindowTitle("测发控组合");
}

TTCcombinationForm::~TTCcombinationForm()
{
    delete ui;
}

void TTCcombinationForm::slot_recv(const QByteArray byte)
{
    qDebug() << "byte.size()" << byte.size();
    QString dataStr(byte.toHex().toUpper());
    qDebug() << "dataStr.size()" << dataStr.size();
    QString displayStr;
    for(int i=0, cnt=dataStr.size(); i < cnt; i++) {
        if(i%2 == 0 && i != 0) {
            displayStr += ' ';
        }
        displayStr += dataStr.at(i);
    }
    ui->labelRecv->setText(displayStr);

    qDebug()<<"TTCcombinationForm:"<<byte.data();
}

void TTCcombinationForm::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    this->hide();
}

void TTCcombinationForm::packData(QByteArray &data)
{
    QDataStream dataStream(&data, QIODevice::Append);
    dataStream.setByteOrder(QDataStream::LittleEndian);	//统一设置为小端模式
    dataStream.setVersion(QDataStream::Qt_4_5);//设置为前期版本，float为32位，double为64位，Qt_4_6以后版本两者长度统一
    bool ok;
    dataStream << (quint8)ui->lineEditCheckState->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditDI01->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditDI23->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditDQ45->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD1->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD2->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD3->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD4->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD5->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD6->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD7->text().toUInt(&ok, 16);
    dataStream << (quint16)ui->lineEditAD8->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime1->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime2->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime3->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime4->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime5->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime6->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime7->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime8->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime9->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime10->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime11->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime12->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime13->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime14->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime15->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime16->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime17->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime18->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime19->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime20->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime21->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime22->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime23->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime24->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime25->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime26->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime27->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime28->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime29->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime30->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime31->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditTime32->text().toUInt(&ok, 16);
    dataStream << (quint32)ui->lineEditT0Time->text().toUInt(&ok, 16);
}

void TTCcombinationForm::packBaseFrame(QByteArray &data)
{
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::LittleEndian);	//统一设置为小端模式
    dataStream.setVersion(QDataStream::Qt_4_5);//设置为前期版本，float为32位，double为64位，Qt_4_6以后版本两者长度统一
    //1,获取基本协议头
    BaseFram_t mBaseFram;
    mBaseFram.head          = 0x4E4A;   //固定值
    mBaseFram.dataLength    = 155;      //数据域固定155Byte
    mBaseFram.SID           = TLC_GROUP;
    mBaseFram.DID           = SERVER;
    mBaseFram.type          = UpType;
    dataStream << mBaseFram;
}

int TTCcombinationForm::sendData(const QByteArray &data)
{
    auto serviceRef = m_context.GetServiceReference<ICommunicationServiceInterface>();

    std::shared_ptr<ICommunicationServiceInterface> com_service =
        m_context.GetService<ICommunicationServiceInterface>(serviceRef);
    if (com_service.get())
    {
       return com_service->sendMessage(CHANNEL_ID_TTCCombination, data);
    }
    else {
        qDebug() << "Get communicationService failed!";
        return 0;
    }
}

void TTCcombinationForm::on_pBtnSend_clicked()
{
    QByteArray datas;
    packBaseFrame(datas);
    packData(datas);
    unsigned char initvalue = 0;
    unsigned char sum = std::accumulate(datas.begin(), datas.end(),initvalue);
    datas.append(sum);

    sendData(datas);
}

void TTCcombinationForm::on_pBtnClear_clicked()
{
    ui->labelRecv->clear();
}
