#ifndef SQLTABLEFORM_H
#define SQLTABLEFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "BundleContext.h"
#include "IGuiService.h"
#include "CommonDefine/commonprotocolstruct.h"

namespace Ui {
class SQLTableForm;
}
using namespace cppmicroservices;

typedef struct PARAFloatInfo_
{
    int code_number;
    float paravalue;
    PARAFloatInfo_() {}
}PARAFloatInfo;
typedef QVector<PARAFloatInfo> PARAFloatVector;
typedef struct PARAByteInfo_
{
    int code_number;
    quint8 paravalue;
    PARAByteInfo_() {}
}PARAByteInfo;
typedef QVector<PARAByteInfo> PARAByteVector;

enum ParamType {
    Type_Float = 0,     //0x00---数值型参数；float 4字节
    Type_Byte           //0x01---状态型参数；BYTE 1字节
};

class SQLTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit SQLTableForm(BundleContext context,QWidget *parent = 0);
    ~SQLTableForm();
    void slot_recv(const QByteArray byte);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_send_clicked();

protected:
    void closeEvent(QCloseEvent *event)Q_DECL_OVERRIDE;

private:
    bool initView1();
    void SQLPARATABLE(QString tablename,int tablenumber,int type);
    void CombFrameAndSend();
    void packSubFrame(QByteArray &dataRet, ParamType type);
    void packBaseFrame(QByteArray &dataRet);
    void getSubHeadArray(const SubFrameHead_t &headVal, QByteArray &dataRet);

private:
    Ui::SQLTableForm *ui;
    QSqlDatabase m_db;
    QSqlTableModel *m_model1;//indextable
    QSqlTableModel *m_model2;//
    //组帧时候查询数据库使用
    QSqlTableModel *m_FramModel1;//indextable
    QSqlTableModel *m_FramModel2;//

    //存放需要发送的数据
    QMap<int,PARAFloatVector> m_floatParaMap;//float类型
    QMap<int,PARAByteVector> m_byteParaMap;//byte类型

    BundleContext m_context;
protected slots:
    void slotRowDoubleClicked(const QModelIndex &index);


};

#endif // SQLTABLEFORM_H
