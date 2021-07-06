#include "tbrawdata.h"

//#define INSERT_SQL              "INSERT INTO %1(%2, %3, %4, %5, %6, %7) VALUES(%8, %9, '%10', %11, %12, '%13');"
#define CREATE_TABLE_SQL        "CREATE TABLE %1( \
                                id int not null auto_increment primary key \
                                sendDate smallint unsigned, \
                                sampleTime int unsigned, \
                                sampleSequence int unsigned, \
                                paraNumber smallint unsigned, \
                                paraCodeNumber smallint unsigned, \
                                paraFlag tinyint unsigned, \
                                dataType int unsigned, \
                                dataValueType tinyint unsigned, \
                                taskId varchar(64), \
                                paraConTent TEXT \
                                );"

#define TABLE_NAME              "CZ2D_RAW_DATA"

TbRawData::TbRawData(SqliteDatabase *dbbase)
    : TbBase(dbbase)
{

}

bool TbRawData::createTable()
{
    QString createSql = QString(CREATE_TABLE_SQL).arg(TABLE_NAME);
    return TbBase::createTable(createSql, TABLE_NAME);
}

bool TbRawData::add(const CommunicationParameterData_t &values)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    bool ret = false;

    QStringList colLst;
    QVariantList valueLst;

    colLst << SEND_DATE << SAMPLE_TIME << SAMPLE_SEQUENCE << PARA_NUMBER << PARA_CODE_NUM
           << PARA_FLAG << DATA_TYPE << DATA_VALUE_TYPE << TASK_ID << PARA_CONTENT;

    /*valueLst << values.sendDate
             << record.value(LINKDEVICE_FIELD_DEV_SN).toInt()
             << record.value(LINKDEVICE_FIELD_DEV_TYPE).toInt()
             << record.value(LINKDEVICE_FIELD_LINK_ID).toInt();*/

    ret = getDatabase()->insertData("TABLE_NAME_LINKDEVICE", colLst, valueLst);

    return ret;
}

