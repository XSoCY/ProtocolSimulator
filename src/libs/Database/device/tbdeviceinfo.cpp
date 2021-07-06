#include "tbdeviceinfo.h"

TbDeviceInfo::TbDeviceInfo(SqliteDatabase *dbbase)
    : TbBase(dbbase)
{

}

bool TbDeviceInfo::createTable()
{
    return TbBase::createTable(CREATE_TABLE_DEVICE_SQL, TABLE_NAME_DEVICEINFO);
}

bool TbDeviceInfo::edit(const QSqlRecord record)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    int ret = -1;

    QMap<QString, QVariant> valueLst;
    valueLst[DEVICEINFO_FIELD_NAME] = record.value(DEVICEINFO_FIELD_NAME).toString();
    valueLst[DEVICEINFO_FIELD_DESCRIPTION] = record.value(DEVICEINFO_FIELD_DESCRIPTION).toString();
    valueLst[DEVICEINFO_FIELD_SUBSYS] = record.value(DEVICEINFO_FIELD_SUBSYS).toInt();
    valueLst[DEVICEINFO_FIELD_SUBSYSSN] = record.value(DEVICEINFO_FIELD_SUBSYSSN).toInt();
    valueLst[DEVICEINFO_FIELD_ISMAIN] = record.value(DEVICEINFO_FIELD_ISMAIN).toInt();
    valueLst[DEVICEINFO_FIELD_OBJECTNAME] = record.value(DEVICEINFO_FIELD_OBJECTNAME).toString();
    valueLst[DEVICEINFO_FIELD_WORKMODE] = record.value(DEVICEINFO_FIELD_WORKMODE).toInt();
    valueLst[DEVICEINFO_FIELD_HEALTHSTATUS] = record.value(DEVICEINFO_FIELD_HEALTHSTATUS).toInt();
    valueLst[DEVICEINFO_FIELD_USESTATUS] = record.value(DEVICEINFO_FIELD_USESTATUS).toInt();
    valueLst[DEVICEINFO_FIELD_TASKID] = record.value(DEVICEINFO_FIELD_TASKID).toString();
    valueLst[DEVICEINFO_FIELD_ISONLINE] = record.value(DEVICEINFO_FIELD_ISONLINE).toInt();
    valueLst[DEVICEINFO_FIELD_SELECTSTATUS] = record.value(DEVICEINFO_FIELD_SELECTSTATUS).toInt();
    valueLst[DEVICEINFO_FIELD_DEV_TYPE] = record.value(DEVICEINFO_FIELD_DEV_TYPE).toInt();

    QMap<QString, QVariant> conditons;
    conditons[DEVICEINFO_FIELD_DEV_ID] = record.value(DEVICEINFO_FIELD_DEV_ID).toInt();
    conditons[DEVICEINFO_FIELD_DEV_SN] = record.value(DEVICEINFO_FIELD_DEV_SN).toInt();

    ret = getDatabase()->updateData(TABLE_NAME_DEVICEINFO, valueLst, conditons);

    return (ret == 0);
}

bool TbDeviceInfo::edit(const QList<QSqlRecord> records)
{
    if( records.size() <= 0 ) return true;

    getDatabase()->transaction();
    foreach (QSqlRecord record, records)
    {
        if( !edit(record) )
        {
            getDatabase()->roback();
            return false;
        }
    }

    return getDatabase()->commit();
}

bool TbDeviceInfo::editWorkMode(uint devId, char cSN, char value)
{
    return editValue(devId, cSN, DEVICEINFO_FIELD_WORKMODE, value);
}

bool TbDeviceInfo::editHealthStatus(uint devId, char cSN, char value)
{
    return editValue(devId, cSN, DEVICEINFO_FIELD_HEALTHSTATUS, value);
}

bool TbDeviceInfo::editUseStatus(uint devId, char cSN, char value)
{
    return editValue(devId, cSN, DEVICEINFO_FIELD_USESTATUS, value);
}

bool TbDeviceInfo::editIsOnline(uint devId, char cSN, char value)
{
    return editValue(devId, cSN, DEVICEINFO_FIELD_ISONLINE, value);
}

bool TbDeviceInfo::editSelectStatus(uint devId, char cSN, char value)
{
    return editValue(devId, cSN, DEVICEINFO_FIELD_SELECTSTATUS, value);
}

int TbDeviceInfo::query(QList<QSqlRecord> &records, str_page_info &pageInfo)
{
    int ret = 0;

    ret = TbBase::getRecords(TABLE_NAME_DEVICEINFO, "", pageInfo, records);

    return ret;
}

void TbDeviceInfo::initQSqlRecord(QSqlRecord &record)
{
    QSqlField field0(DEVICEINFO_FIELD_DEV_ID);
    record.append(field0);

    QSqlField field1(DEVICEINFO_FIELD_DEV_SN);
    record.append(field1);

    QSqlField field2(DEVICEINFO_FIELD_NAME);
    record.append(field2);

    QSqlField field3(DEVICEINFO_FIELD_DESCRIPTION);
    record.append(field3);

    QSqlField field4(DEVICEINFO_FIELD_SUBSYS);
    record.append(field4);

    QSqlField field5(DEVICEINFO_FIELD_SUBSYSSN);
    record.append(field5);

    QSqlField field6(DEVICEINFO_FIELD_ISMAIN);
    record.append(field6);

    QSqlField field7(DEVICEINFO_FIELD_OBJECTNAME);
    record.append(field7);

    QSqlField field8(DEVICEINFO_FIELD_WORKMODE);
    record.append(field8);

    QSqlField field9(DEVICEINFO_FIELD_HEALTHSTATUS);
    record.append(field9);

    QSqlField field10(DEVICEINFO_FIELD_USESTATUS);
    record.append(field10);

    QSqlField field11(DEVICEINFO_FIELD_TASKID);
    record.append(field11);

    QSqlField field12(DEVICEINFO_FIELD_ISONLINE);
    record.append(field12);

    QSqlField field13(DEVICEINFO_FIELD_SELECTSTATUS);
    record.append(field13);

    QSqlField field14(DEVICEINFO_FIELD_DEV_TYPE);
    record.append(field14);
}

bool TbDeviceInfo::editValue(uint devId, char cSN, QString fieldName, char value)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    int ret = -1;

    QMap<QString, QVariant> valueLst;
    valueLst[fieldName] = value;

    QMap<QString, QVariant> conditons;
    valueLst[DEVICEINFO_FIELD_DEV_ID] = devId;
    valueLst[DEVICEINFO_FIELD_DEV_SN] = cSN;

    ret = getDatabase()->updateData(TABLE_NAME_DEVICEINFO, valueLst, conditons);

    return (ret == 0);
}
