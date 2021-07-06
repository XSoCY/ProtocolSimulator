#ifndef TBPARAMMACRO_H
#define TBPARAMMACRO_H

#include "tbbase.h"

#define CREATE_TABLE_PARAMMACRO_SQL    "CREATE TABLE \"DMBMonitor\".\"PARAMMACRO\" \
                                        ( \
                                        \"ID\" INT IDENTITY(1, 1) NOT NULL, \
                                        \"MACRO_ID\" INT, \
                                        \"NAME\" VARCHAR(32), \
                                        \"DESCRIPTION\" VARCHAR(128), \
                                        \"SYSWORKMODE\" VARCHAR(8), \
                                        \"SYSWORKMODE2\" INT, \
                                        \"TASKID\" BLOB, \
                                        \"TASKMARK\" BLOB, \
                                        \"TARGETSUM\" INT, \
                                        \"SAMEWARE\" INT, \
                                        \"UPFRQ\" BLOB, \
                                        \"DOWNFRQ\" BLOB, \
                                        \"DEVMODELDX\" BLOB, \
                                        NOT CLUSTER PRIMARY KEY(\"ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR);"

#define PARAMMACRO_SELECT_SQL           "SELECT * FROM %1 "
#define PARAMMACRO_DELETE_SQL           "DELETE FROM %1 "
#define TABLE_NAME_PARAMMACRO           "\"DMBMonitor\".\"PARAMMACRO\""

#define PARAMMACRO_FIELD_ID             "ID"
#define PARAMMACRO_FIELD_MACRO_ID       "MACRO_ID"
#define PARAMMACRO_FIELD_NAME           "NAME"
#define PARAMMACRO_FIELD_DESCRIPTION    "DESCRIPTION"
#define PARAMMACRO_FIELD_SYSWORKMODE    "SYSWORKMODE"
#define PARAMMACRO_FIELD_SYSWORKMODE2   "SYSWORKMODE2"
#define PARAMMACRO_FIELD_TASKID         "TASKID"
#define PARAMMACRO_FIELD_TASKMARK       "TASKMARK"
#define PARAMMACRO_FIELD_TARGETSUM      "TARGETSUM"
#define PARAMMACRO_FIELD_SAMEWARE       "SAMEWARE"
#define PARAMMACRO_FIELD_UPFRQ          "UPFRQ"
#define PARAMMACRO_FIELD_DOWNFRQ        "DOWNFRQ"
#define PARAMMACRO_FIELD_DEVMODELDX     "DEVMODELDX"

class DATABASESHARED_EXPORT TbParamMacro : public TbBase
{
public:
    TbParamMacro(SqliteDatabase *dbbase);

    /**
     * @brief createTable 创建表
     * @param tableName 创建的表名称
     * @return true-成功；false-失败；
     */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool addParamMacro(const QSqlRecord &recordMain, const QList<QSqlRecord> &records);
    bool del(const QSqlRecord &record);
    bool del(const unsigned int &macroId);
    bool delWholes(const QList<QSqlRecord> &records);
    bool delWholes(const QList<unsigned int> &macroIds);
    bool edit(const QSqlRecord &record);

    int  query(QList<QSqlRecord> &records);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
    int queryForMacroId(uint macroId, QList<QSqlRecord> &records);
    void initQSqlRecord(QSqlRecord &record);
};

#endif // TBPARAMMACRO_H
