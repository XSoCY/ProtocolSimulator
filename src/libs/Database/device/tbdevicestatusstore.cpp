#include "tbdevicestatusstore.h"

TbDeviceStatusStore::TbDeviceStatusStore(SqliteDatabase *dbbase)
    :TbBase(dbbase)
{
}

bool TbDeviceStatusStore::createTable(const QString &nameSuffix)
{
    QString fullCreattableSql = QString(CREATE_TABLE_DEVICESTATUS_SQL).arg(nameSuffix);
    QString fullTablename = QString(TABLE_NAME_DEVICESTATUS).arg(nameSuffix);
    return TbBase::createTable(fullCreattableSql, fullTablename);
}

QString TbDeviceStatusStore::getFullTbname(const QString &nameSuffix)
{
    return QString(TABLE_NAME_DEVICESTATUS).arg(nameSuffix);
}

bool TbDeviceStatusStore::isTableNameExistWithSuffix(const QString &nameSuffix)
{
    QString fuName = getFullTbname(nameSuffix);
    return isTableExist(fuName);
}


bool TbDeviceStatusStore::addOneStatusData(const QString &nameSuffix, const DeviceStatusStruct &oneStatusData)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;


    bool ret = false;

    QStringList colLst;
    QVariantList valueLst;

    colLst << DEVICEINFO_FIELD_TIME
           << DEVICEINFO_FIELD_DEVID
           << DEVICEINFO_FIELD_DEVTYPE
           << DEVICEINFO_FIELD_DEVDATA;

    valueLst << oneStatusData.strTime
             << oneStatusData.deviceID
             << oneStatusData.deviceType
             << oneStatusData.deviceStatusData;

    QString fullTablename = QString(TABLE_NAME_DEVICESTATUS).arg(nameSuffix);

    ret = getDatabase()->insertData(fullTablename, colLst, valueLst);

    return ret;


}

bool TbDeviceStatusStore::addStatusDatas(const QString &nameSuffix, const QList<DeviceStatusStruct> &listStatusData)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    getDatabase()->transaction();

    for(int i = 0; i < listStatusData.size(); i++)
    {
        if(!addOneStatusData(nameSuffix, listStatusData[i]))
        {
            getDatabase()->roback();
            return false;
        }
    }
    return getDatabase()->commit();
#if 0
    bool ret = false;

    QStringList colLst;

    QList<QVariantList> allData;
    QVariantList valueLst;

    colLst << DEVICEINFO_FIELD_TIME
           << DEVICEINFO_FIELD_DEVID
           << DEVICEINFO_FIELD_DEVTYPE
           << DEVICEINFO_FIELD_DEVDATA;


    for(int i = 0; i < listStatusData.size(); i++)
    {
        valueLst << listStatusData[i].strTime
                 << listStatusData[i].deviceID
                 << listStatusData[i].deviceType
                 << listStatusData[i].deviceStatusData;
        allData.append(valueLst);
    }

    QString fullTablename = QString(TABLE_NAME_DEVICESTATUS).arg(nameSuffix);

    ret = getDatabase()->insertData(fullTablename, colLst, allData);
    return ret;
#endif
}

int TbDeviceStatusStore::query(QList<QSqlRecord> &records, QString strTableTime, QString strQueryInfo)
{
    int ret = 0;

    ret = TbBase::getDevieceStatus(TABLE_NAME_DEVICESTATUS, strTableTime, strQueryInfo, records);

    return ret;
}


