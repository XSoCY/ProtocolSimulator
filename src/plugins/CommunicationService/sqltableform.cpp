#include "sqltableform.h"
#include "ui_sqltableform.h"
#include <QDebug>
#include <QSqlRecord>
#include <QTime>
#include "ICommunicationService.h"
#include "communication_define.h"
#include "util/CConverter.h"
#include "worker.h"

SQLTableForm::SQLTableForm(BundleContext context,QWidget *parent) :
    QWidget(parent),m_context(context),
    ui(new Ui::SQLTableForm)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("192.168.2.80");
    m_db.setDatabaseName("protocolsimulator");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    bool ok = m_db.open();
    if(!ok)
    {
        qDebug()<<"db open error";
        return ;
    }
    m_model1 = new QSqlTableModel(this, m_db);
    m_model2 = new QSqlTableModel(this, m_db);
    m_FramModel1 = new QSqlTableModel(this, m_db);//indextable
    m_FramModel2 = new QSqlTableModel(this, m_db);//
    ui->tableView->setModel(m_model1);
    ui->tableView_2->setModel(m_model2);
    initView1();
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(slotRowDoubleClicked(const QModelIndex &)));

    initThread();
}

SQLTableForm::~SQLTableForm()
{
    m_db.close();
    delete ui;
}

bool SQLTableForm::initView1()
{
    m_model1->setTable("indextable");
    m_model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model1->select();
    //ui->tableView->hideColumn(0); // don't show the ID
    return true;
}

void SQLTableForm::initThread()
{
    Worker *worker = new Worker;
    worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &SQLTableForm::startAutoSend, worker, &Worker::startAutoSend);
    connect(this, &SQLTableForm::stopAutoSend, worker, &Worker::stopAutoSend);
    connect(worker, &Worker::sendData, this, &SQLTableForm::CombFrameAndSend, Qt::DirectConnection);
    m_workerThread.start();
}

void SQLTableForm::SQLPARATABLE(QString tablename,int tablenumber,int type)
{
    m_FramModel2->setTable(tablename);
    m_FramModel2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_FramModel2->select();
    int mRows2 = m_FramModel2->rowCount();
    PARAFloatVector fparavector;
    PARAByteVector bparavector;

    for(int j = 0 ; j < mRows2 ;j++)
    {
        QSqlRecord record2 = m_FramModel2->record(j);
        int mState2 = record2.value("CHEACK_STATE").toInt();
        if(mState2 == 0)
        {
            continue;
        }
        PARAFloatInfo fpara;
        PARAByteInfo  bpara;
        if(type == 0)
        {
            fpara.paravalue = record2.value("PARA_VALUE").toFloat();
            fpara.code_number = record2.value("PARA_CODE_NUMBER").toInt();
            fparavector.push_back(fpara);
        }
        else if(type == 1)
        {
            bpara.paravalue = record2.value("PARA_VALUE").toInt();
            bpara.code_number = record2.value("PARA_CODE_NUMBER").toInt();
            bparavector.push_back(bpara);
        }
    }
    if(type == 0)
    {
        if(fparavector.size() > 0)
        {
            m_floatParaMap.insert(tablenumber,fparavector);
        }

    }
    else if(type == 1)
    {
        if(bparavector.size() > 0)
        {
            m_byteParaMap.insert(tablenumber,bparavector);
        }
    }

}
//组合帧  且  发送网络。
void SQLTableForm::CombFrameAndSend()
{
    auto serviceRef = m_context.GetServiceReference<ICommunicationServiceInterface>();

    std::shared_ptr<ICommunicationServiceInterface> com_service =
        m_context.GetService<ICommunicationServiceInterface>(serviceRef);
    if (com_service.get())
    {
       QByteArray array;
       packBaseFrame(array);
       com_service->sendMessage(CHANNEL_ID_Equipment,array);
    }
    else {
        qDebug() << "error";
    }
}

void SQLTableForm::packSubFrame(QByteArray &dataRet, ParamType type)
{
    //获取子数据段协议头
    SubFrameHead_t subFramHead;
    subFramHead.time = QTime::currentTime().msecsSinceStartOfDay()*10;    //系统当前时间 量化单位0.1ms
    QByteArray subData;
    if(type == Type_Float) {
        subFramHead.paramType = 0x00;
        QMap<int,PARAFloatVector>::iterator iter = m_floatParaMap.begin();
        for(; iter != m_floatParaMap.end(); iter++) {
            //subData.append(CConverter::ushortToByte(iter.key()));  //表号
            subFramHead.tableNum = iter.key();
            foreach (PARAFloatInfo data, iter.value()) {
                subData.append(CConverter::ushortToByte(data.code_number)); //参数序号
                subData.append(CConverter::floatToByte(data.paravalue));    //参数值
                subData.append(char(0));   //超差标识暂时填0
                subFramHead.length += 7;
            }
            uchar tail[2] = {0xFF, 0xFF};
            subData.append((char*)tail, 2);     //子段尾
            subFramHead.length += 2;
            QByteArray headArray;
            getSubHeadArray(subFramHead, headArray);
            dataRet.append(headArray);
            dataRet.append(subData);
            subFramHead.length = 0;
            subData.clear();
        }
    } else {
        subFramHead.paramType = 0x01;
        QMap<int,PARAByteVector>::iterator iter = m_byteParaMap.begin();
        for(; iter != m_byteParaMap.end(); iter++) {
            //subData.append(CConverter::intToByte(iter.key()));  //表号
            subFramHead.tableNum = iter.key();
            foreach (PARAByteInfo data, iter.value()) {
                subData.append(CConverter::ushortToByte(data.code_number)); //参数序号
                subData.append(data.paravalue);     //参数值
                subData.append(char(0));            //超差标识暂时填0
                subFramHead.length += 4;
            }
            uchar tail[2] = {0xFF, 0xFF};
            subData.append((char*)tail, 2);     //子段尾
            subFramHead.length += 2;
            QByteArray headArray;
            getSubHeadArray(subFramHead, headArray);
            dataRet.append(headArray);
            dataRet.append(subData);
            subFramHead.length = 0;
            subData.clear();
        }
    }
}

void SQLTableForm::packBaseFrame(QByteArray &dataRet)
{
    QDataStream dataStream(&dataRet, QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::LittleEndian);	//统一设置为小端模式
    dataStream.setVersion(QDataStream::Qt_4_5);//设置为前期版本，float为32位，double为64位，Qt_4_6以后版本两者长度统一
    //1,获取基本协议头
    BaseFram_t mBaseFram;
    mBaseFram.head          = 0x4E4A;   //固定值
    mBaseFram.SID           = SYNTHESIS_CONTROL_COMPUTER;
    mBaseFram.DID           = SERVER;
    mBaseFram.type          = UpType;

    QByteArray subFramData;
    packSubFrame(subFramData, Type_Float);
    packSubFrame(subFramData, Type_Byte);
    mBaseFram.dataLength = subFramData.size();
    dataStream << mBaseFram;
    //校验和
    unsigned char initvalue = 0;
    unsigned char sum = std::accumulate(subFramData.begin(), subFramData.end(),initvalue);
    subFramData.append(sum);

    dataRet.append(subFramData);
}

void SQLTableForm::getSubHeadArray(const SubFrameHead_t &headVal, QByteArray &dataRet)
{
    QDataStream dataStream(&dataRet, QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream.setVersion(QDataStream::Qt_4_5);

    dataStream << headVal;
}

void SQLTableForm::slotRowDoubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {

        QSqlRecord record = m_model1->record(index.row());
        QString value = record.value("TABLE_NAME").toString();
        int mType = record.value("PARA_TYPE").toInt();

        m_model2->setTable(value);
        m_model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
        m_model2->select();
        if(0 == mType)
        {
            ui->tableView_2->hideColumn(8);
            ui->tableView_2->hideColumn(10);
            ui->tableView_2->hideColumn(11);
            ui->tableView_2->hideColumn(12);
            ui->tableView_2->hideColumn(13);
        }
        else if(1 == mType)
        {
            ui->tableView_2->hideColumn(8);
            ui->tableView_2->hideColumn(9);
            ui->tableView_2->hideColumn(10);
            ui->tableView_2->hideColumn(11);
            ui->tableView_2->hideColumn(12);

        }
        else if(2 == mType)
        {
            ui->tableView_2->hideColumn(5);
            ui->tableView_2->hideColumn(6);
            ui->tableView_2->hideColumn(7);
            ui->tableView_2->hideColumn(8);
            ui->tableView_2->hideColumn(9);

        }
    }

}

void SQLTableForm::slot_recv(const QByteArray byte)
{

    qDebug()<<"SQLTableForm:"<<byte.data();
}


void SQLTableForm::on_pushButton_clicked()
{
    m_model1->database().transaction(); //开始事务操作
    if (m_model1->submitAll()) // 提交所有被修改的数据到数据库中
    {
        m_model1->database().commit(); //提交成功，事务将真正修改数据库数据
    } else {
        m_model1->database().rollback(); //提交失败，事务回滚

    }
    //m_model1->revertAll(); //撤销修改
}

void SQLTableForm::on_pushButton_2_clicked()
{
    m_model2->database().transaction(); //开始事务操作
    if (m_model2->submitAll()) // 提交所有被修改的数据到数据库中
    {
        m_model2->database().commit(); //提交成功，事务将真正修改数据库数据
    } else {
        m_model2->database().rollback(); //提交失败，事务回滚

    }
}
/*************************************************************************
*    class        : sqltableform.cpp
*    Function     : 发送网络数据，组织indextable中选中状态为1的所有参数表的参数，然后筛选参数选中状态为1的值 ，组帧，然后发送。
*    Parameters   :
*    ReturnValue  ：
*    Author       : FengYu
*    Time         : 2021-06-29  11:44
*    others       :
**************************************************************************/
void SQLTableForm::on_pushButton_send_clicked()
{
    m_floatParaMap.clear();
    m_byteParaMap.clear();
    m_FramModel1->setTable("indextable");
    m_FramModel1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_FramModel1->select();
    int mRows = m_FramModel1->rowCount();
    for(int i = 0 ; i < mRows ;i++)
    {
        QSqlRecord record = m_FramModel1->record(i);
        int mState = record.value("CHEACK_STATE").toInt();
        if(mState == 0)
        {
            continue;
        }
//        int mType = record.value("PARA_TYPE").toInt();
        QString value = record.value("TABLE_NAME").toString();
        int tablenumber = record.value("PARA_TABLE_NUMBER").toInt();
        int type = record.value("PARA_TYPE").toInt();

        SQLPARATABLE(value,tablenumber,type);
    }
    CombFrameAndSend();
}

void SQLTableForm::closeEvent(QCloseEvent *event)
{
    this->hide();
}

void SQLTableForm::on_checkBox_send_clicked(bool checked)
{
    if(checked) {
        emit startAutoSend(ui->spinBox->value());
    } else {
        emit stopAutoSend();
    }
}

void SQLTableForm::on_spinBox_valueChanged(int arg1)
{
    if(ui->checkBox_send->isChecked()) {
        emit startAutoSend(arg1);
    }
}
