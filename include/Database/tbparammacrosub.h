#ifndef TBPARAMMACROSUB_H
#define TBPARAMMACROSUB_H

#include "tbbase.h"

#define CREATE_TABLE_PARAMMACROSUB_SQL  "CREATE TABLE \"DMBMonitor\".\"PARAMMACRO_SUB\" \
                                        ( \
                                        \"MACRO_ID\" INT NOT NULL,  \
                                        \"DEVICE_ID\" INT NOT NULL, \
                                        \"CMD_TYPE\" INT NOT NULL, \
                                        \"MODUCARRIER_ID\" DOUBLE NOT NULL, \
                                        \"DATA_LEN\" INT, \
                                        \"CMD_DATA\" BLOB, \
                                        NOT CLUSTER PRIMARY KEY(\"MACRO_ID\", \"DEVICE_ID\", \"CMD_TYPE\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define PARAMMACROSUB_DELETE_SQL        "DELETE FROM %1 "
#define TABLE_NAME_PARAMMACROSUB        "\"DMBMonitor\".\"PARAMMACRO_SUB\""

#define PARAMMACROSUB_FIELD_MACRO_ID    "MACRO_ID"
#define PARAMMACROSUB_FIELD_DEVICE_ID   "DEVICE_ID"
#define PARAMMACROSUB_FIELD_DEVICE_SN   "DEVICE_SN"
#define PARAMMACROSUB_FIELD_MODUCARRIER_ID   "MODUCARRIER_ID"
#define PARAMMACROSUB_FIELD_CMD_TYPE    "CMD_TYPE"                                                     
#define PARAMMACROSUB_FIELD_DATA_LEN    "DATA_LEN"
#define PARAMMACROSUB_FIELD_CMD_DATA    "CMD_DATA"


class DATABASESHARED_EXPORT TbParamMacroSub : public TbBase
{
public:
    TbParamMacroSub(SqliteDatabase *dbbase);

    /**
     * @brief createTable 创建表
     * @return true-成功；false-失败；
     */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool adds(const QList<QSqlRecord> &record);
    bool del(const QSqlRecord &record);
    bool delForMacroID(const unsigned int &macroId);
    bool edit(const QSqlRecord &record);

    int  query(QList<QSqlRecord> &records);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
    int  queryForMacroId(uint macroId, QList<QSqlRecord> &records);
    void initQSqlRecord(QSqlRecord &record);
};

#endif // TBPARAMMACRO_H
