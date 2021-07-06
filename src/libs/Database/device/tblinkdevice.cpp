#include "tblinkdevice.h"

TbLinkDevice::TbLinkDevice(SqliteDatabase *dbbase)
    : TbBase(dbbase)
{

}

bool TbLinkDevice::createTable()
{
    return TbBase::createTable(CREATE_TABLE_LINKDEVICE_SQL, TABLE_NAME_LINKDEVICE);
}

bool TbLinkDevice::add(const QSqlRecord &record)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    bool ret = false;

    QStringList colLst;
    QVariantList valueLst;

    colLst << LINKDEVICE_FIELD_DEV_ID
           << LINKDEVICE_FIELD_DEV_SN
           << LINKDEVICE_FIELD_DEV_TYPE
           << LINKDEVICE_FIELD_LINK_ID;

    valueLst << record.value(LINKDEVICE_FIELD_DEV_ID).toInt()
             << record.value(LINKDEVICE_FIELD_DEV_SN).toInt()
             << record.value(LINKDEVICE_FIELD_DEV_TYPE).toInt()
             << record.value(LINKDEVICE_FIELD_LINK_ID).toInt();

    ret = getDatabase()->insertData(TABLE_NAME_LINKDEVICE, colLst, valueLst);

    return ret;
}

bool TbLinkDevice::add(const QList<QSqlRecord> &records)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    getDatabase()->transaction();

    foreach (QSqlRecord record, records)
    {
        if( !add(record) )
        {
            getDatabase()->roback();
            return false;
        }
    }

    return getDatabase()->commit();
}

bool TbLinkDevice::del()
{
    return TbBase::del(TABLE_NAME_LINKDEVICE, "");
}

bool TbLinkDevice::del(const QSqlRecord &record)
{
    char linkId = record.value(LINKDEVICE_FIELD_LINK_ID).toChar().toLatin1();
    return del(linkId);
}

bool TbLinkDevice::del(const char &linkId)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QString swhere = " WHERE %1=%2 ";

    swhere = swhere.arg(LINKDEVICE_FIELD_LINK_ID).arg(linkId);

    return TbBase::del(TABLE_NAME_LINKDEVICE, swhere);
}

bool TbLinkDevice::del(const QList<char> &linkIds)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    getDatabase()->transaction();

    foreach (char linkId, linkIds)
    {
        if( !del(linkId) )
        {
            getDatabase()->roback();
            return false;
        }
    }

    return getDatabase()->commit();
}

bool TbLinkDevice::edit(const char linkId, const QList<QSqlRecord> &records)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    bool ret = false;
    if( del(linkId) )
    {
        ret = add(records);
    }

    return ret;
}

bool TbLinkDevice::edit(const QList<QSqlRecord> &records)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    bool ret = false;
    if( del() )
    {
        ret = add(records);
    }

    return ret;
}

int  TbLinkDevice::query(QList<QSqlRecord> &records)
{
    return TbBase::getRecords(TABLE_NAME_LINKDEVICE, "", records);
}

int  TbLinkDevice::queryForLinkId(char linkId, QList<QSqlRecord> &records)
{
    QString swhere = " WHERE %1=%2";

    swhere = swhere.arg(LINKDEVICE_FIELD_LINK_ID).arg(linkId);

    return TbBase::getRecords(TABLE_NAME_LINKDEVICE, swhere, records);
}

void TbLinkDevice::initQSqlRecord(QSqlRecord &record)
{
    QSqlField field0(LINKDEVICE_FIELD_DEV_ID);
    record.append(field0);

    QSqlField field1(LINKDEVICE_FIELD_DEV_SN);
    record.append(field1);

    QSqlField field2(LINKDEVICE_FIELD_DEV_TYPE);
    record.append(field2);

    QSqlField field3(LINKDEVICE_FIELD_LINK_ID);
    record.append(field3);
}
