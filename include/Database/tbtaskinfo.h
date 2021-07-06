#ifndef TBTASKINFO_H
#define TBTASKINFO_H

#include "tbbase.h"

#define CREATE_TABLE_TASKINFO_SQL   "CREATE TABLE \"DMBMonitor\".\"TASKINFO\" \
                                    ( \
                                    \"ID\" INT IDENTITY(1, 1) NOT NULL, \
                                    \"TASKID\" INT, \
                                    \"DESCRIPTION\" VARCHAR(256), \
                                    \"STATUS\" INT, \
                                    \"WORKMODE\" INT, \
                                    \"TASKCODE\" VARCHAR(7), \
                                    \"TASKMARK\" INT, \
                                    \"CM_ID\" INT, \
                                    \"PM_ID\" INT, \
                                    \"LINK_ID\" INT, \
                                    UNIQUE(\"TASKID\"), \
                                    NOT CLUSTER PRIMARY KEY(\"ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define TASKINFO_SELECT_SQL         "SELECT * FROM %1 "
#define TASKINFO_DELETE_SQL         "DELETE FROM %1 "
#define TABLE_NAME_TASKINFO         "\"DMBMonitor\".\"TASKINFO\""

#define TASKINFO_FIELD_ID           "ID"
#define TASKINFO_FIELD_TASKID       "TASKID"
#define TASKINFO_FIELD_TASKCODE     "TASKCODE"
#define TASKINFO_FIELD_TASKMARK     "TASKMARK"
#define TASKINFO_FIELD_DESCRIPTION  "DESCRIPTION"
#define TASKINFO_FIELD_STATUS       "STATUS"
#define TASKINFO_FIELD_WORKMODE     "WORKMODE"
#define TASKINFO_FIELD_CM_ID        "CM_ID"
#define TASKINFO_FIELD_PM_ID        "PM_ID"
#define TASKINFO_FIELD_LINK_ID      "LINK_ID"

class DATABASESHARED_EXPORT TbTaskInfo : public TbBase
{
public:
    TbTaskInfo(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);

    bool del(const QSqlRecord &record);
    bool del(const uint &taskId);
    bool delTaskInfoTrans(const QList<uint> &taskIds);

    bool edit(const QSqlRecord &ruintecord);
    bool editStatus(const uint &taskId, char status);
    bool editParamMacro(const uint &taskId, uint paramMacroId);
    bool editLinkId(const uint &taskId, char linkId);
    bool editLinkIdAndParamMacro(const uint &taskId, char linkId, uint paramMacroId);

    int  query(QList<QSqlRecord> &records);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
    int  queryForTaskId(uint macroId, QList<QSqlRecord> &records);

    void initQSqlRecord(QSqlRecord &record);
};

#endif // TBTASKINFO_H
