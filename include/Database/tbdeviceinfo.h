#ifndef TBDEVICEINFO_H
#define TBDEVICEINFO_H

#include "tbbase.h"

#define CREATE_TABLE_DEVICE_SQL     "CREATE TABLE \"DMBMonitor\".\"DEVICEINFO\" \
                                    ( \
                                    \"DEV_ID\" INT NOT NULL, \
                                    \"DEV_SN\" INT NOT NULL, \
                                    \"NAME\" VARCHAR(32), \
                                    \"DESCRIPTION\" VARCHAR(128), \
                                    \"SUBSYS\" INT, \
                                    \"SUBSYSSN\" INT, \
                                    \"ISMAIN\" INT, \
                                    \"OBJECTNAME\" VARCHAR(128), \
                                    \"WORKMODE\" INT, \
                                    \"HEALTHSTATUS\" INT, \
                                    \"USESTATUS\" INT, \
                                    \"TASKID\" CHAR(6), \
                                    \"ISONLINE\" INT, \
                                    \"SELECTSTATUS\" INT, \
                                    \"DEV_TYPE\" INT, \
                                    CLUSTER PRIMARY KEY(\"DEV_ID\", \"DEV_SN\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define DEVICEINFO_SELECT_SQL           "SELECT * FROM %1 "
#define DEVICEINFO_DELETE_SQL           "DELETE FROM %1 "
#define TABLE_NAME_DEVICEINFO           "\"DMBMonitor\".\"DEVICEINFO\""

#define DEVICEINFO_FIELD_DEV_ID         "DEV_ID"
#define DEVICEINFO_FIELD_DEV_SN         "DEV_SN"
#define DEVICEINFO_FIELD_NAME           "NAME"
#define DEVICEINFO_FIELD_DESCRIPTION    "DESCRIPTION"
#define DEVICEINFO_FIELD_SUBSYS         "SUBSYS"
#define DEVICEINFO_FIELD_SUBSYSSN       "SUBSYSSN"
#define DEVICEINFO_FIELD_ISMAIN         "ISMAIN"
#define DEVICEINFO_FIELD_OBJECTNAME     "OBJECTNAME"
#define DEVICEINFO_FIELD_WORKMODE       "WORKMODE"
#define DEVICEINFO_FIELD_HEALTHSTATUS   "HEALTHSTATUS"
#define DEVICEINFO_FIELD_USESTATUS      "USESTATUS"
#define DEVICEINFO_FIELD_TASKID         "TASKID"
#define DEVICEINFO_FIELD_ISONLINE       "ISONLINE"
#define DEVICEINFO_FIELD_SELECTSTATUS   "SELECTSTATUS"
#define DEVICEINFO_FIELD_DEV_TYPE       "DEV_TYPE"

class DATABASESHARED_EXPORT TbDeviceInfo : public TbBase
{
public:
    TbDeviceInfo(SqliteDatabase *dbbase);

    bool createTable();
    bool edit(const QSqlRecord record);
    bool edit(const QList<QSqlRecord> records);
    bool editWorkMode(uint devId, char cSN, char value);
    bool editHealthStatus(uint devId, char cSN, char value);
    bool editUseStatus(uint devId, char cSN, char value);
    bool editIsOnline(uint devId, char cSN, char value);
    bool editSelectStatus(uint devId, char cSN, char value);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);

    void initQSqlRecord(QSqlRecord &record);
private:
    bool editValue(uint devId, char cSN, QString fieldName, char value);
};

#endif // TBDEVICEINFO_H
