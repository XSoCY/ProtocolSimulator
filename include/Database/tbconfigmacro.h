#ifndef TBDEVCONFIGMACROINFORMATION_H
#define TBDEVCONFIGMACROINFORMATION_H

#include "tbbase.h"

#define CREATE_TABLE_CONFIGMACRO_SQL    "CREATE TABLE \"DMBMonitor\".\"CONFIGMACRO\" \
                                        ( \
                                        \"CM_ID\" INT NOT NULL, \
                                        \"NAME\" VARCHAR(32), \
                                        \"MODE\" INT, \
                                        \"FLAG\" INT, \
                                        \"BASEID\" INT, \
                                        \"DESCRIPTION\" VARCHAR(128), \
                                        \"OSM_CMD_DATA\" BLOB, \
                                        \"TS_CMD_DATA\" BLOB, \
                                        CLUSTER PRIMARY KEY(\"CM_ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ; "

#define CONFIGMACRO_SELECT_SQL           "SELECT * FROM %1 "
#define CONFIGMACRO_DELETE_SQL           "DELETE FROM %1 "
#define TABLE_NAME_CONFIGMACRO           "\"DMBMonitor\".\"CONFIGMACRO\""

#define CONFIGMACRO_FIELD_CM_ID          "CM_ID"
#define CONFIGMACRO_FIELD_NAME           "NAME"
#define CONFIGMACRO_FIELD_MODE           "MODE"
#define CONFIGMACRO_FIELD_FLAG           "FLAG"
#define CONFIGMACRO_FIELD_BASEID         "BASEID"
#define CONFIGMACRO_FIELD_DESCRIPTION    "DESCRIPTION"
#define CONFIGMACRO_FIELD_OSM_CMD_DATA   "OSM_CMD_DATA"
#define CONFIGMACRO_FIELD_TS_CMD_DATA    "TS_CMD_DATA"

class DATABASESHARED_EXPORT TbConfigMacro : public TbBase
{
public:
    TbConfigMacro(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool add(const QSqlRecord &record, QList<QSqlRecord> linkDevices);

    bool del(const QSqlRecord &record);
    bool del(const uint &configMacroId);
    bool del(const QList<uint> &cmIds);
    bool delConfigMarcoAadLinkDevTrans(const uint &cmId);
    bool delConfigMarcoAadLinkDevTrans(const QList<uint> &cmIds);

    bool edit(const QSqlRecord &record);
    bool edit(const QSqlRecord &record, QList<QSqlRecord> linkDevices);

    int  query(QList<QSqlRecord> &records);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
    int  queryForMacroId(uint macroId, QList<QSqlRecord> &records);

    void initQSqlRecord(QSqlRecord &record);

private:
    bool delConfigMarcoAadLinkDev(const uint &cmId);
};

#endif // TBDEVCONFIGMACROINFORMATION_H
