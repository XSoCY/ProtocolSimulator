#ifndef TBDEVICESTATUSSTORE_H
#define TBDEVICESTATUSSTORE_H

#include "tbbase.h"


#define CREATE_TABLE_DEVICESTATUS_SQL     "CREATE TABLE \"DMBMonitor\".\"DEVICESTATUS_%1\" \
( \
\"TIME\" TIMESTAMP(6), \
\"DEVICE_ID\" INT, \
\"DEVICE_TYPE\" INT, \
\"STATUSDATA\" BLOB) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"


#define TABLE_NAME_DEVICESTATUS          "\"DMBMonitor\".\"DEVICESTATUS_%1\""

#define DEVICEINFO_FIELD_TIME           "TIME"
#define DEVICEINFO_FIELD_DEVID          "DEVICE_ID"
#define DEVICEINFO_FIELD_DEVTYPE        "DEVICE_TYPE"
#define DEVICEINFO_FIELD_DEVDATA        "STATUSDATA"

#pragma pack(1)
typedef struct DeviceStatusStruct
{
    QString     strTime;            //接收时间
    uint        deviceID;           //设备id
    uint        deviceType;         //设备类型
    QByteArray  deviceStatusData;   //设备状态
}DeviceStatusStruct_t;
#pragma pack()
namespace DeviceStatusTBDefinition
{
const QString s_timeformatField = "yyyy-MM-dd hh:mm:ss"; // 设备存储时间格式
const QString s_timeformatDBName = "yyyyMMdd"; // 设备数据库表
}

class DATABASESHARED_EXPORT TbDeviceStatusStore : public TbBase
{
public:
    TbDeviceStatusStore(SqliteDatabase *dbbase);

public:
    bool createTable(const QString& nameSuffix);
    QString getFullTbname(const QString &nameSuffix);
    bool isTableNameExistWithSuffix(const QString& nameSuffix);

    bool addOneStatusData(const QString& nameSuffix, const DeviceStatusStruct& oneStatusData);
    bool addStatusDatas(const QString& nameSuffix, const QList<DeviceStatusStruct>& listStatusData);
    int  query(QList<QSqlRecord> &records, QString strTableTime, QString strQueryInfo);
};

#endif // TBDEVICESTATUSSTORE_H
