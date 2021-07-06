#ifndef TBLINKINFO_H
#define TBLINKINFO_H

#include "tbbase.h"

#define CREATE_TABLE_TASKPLANNING_SQL   "CREATE TABLE \"DMBMonitor\".\"TASKPLANNING\" \
                                        ( \
                                        \"LINK_ID\" INT NOT NULL, \
                                        \"TASKID\" INT, \
                                        \"MODE\" INT, \
                                        \"STATUS\" INT, \
                                        \"ISAUTO\" INT, \
                                        \"RUNSTATUS\" INT, \
                                        CLUSTER PRIMARY KEY(\"LINK_ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define TASKPLANNING_SELECT_SQL         "SELECT * FROM %1 "
#define TASKPLANNING_DELETE_SQL         "DELETE FROM %1 "
#define TABLE_NAME_TASKPLANNING         "\"DMBMonitor\".\"TASKPLANNING\""

#define TASKPLANNING_FIELD_LINK_ID      "LINK_ID"
#define TASKPLANNING_FIELD_TASKID       "TASKID"
#define TASKPLANNING_FIELD_MODE         "MODE"
#define TASKPLANNING_FIELD_STATUS       "STATUS"
#define TASKPLANNING_FIELD_ISAUTO       "ISAUTO"
#define TASKPLANNING_FIELD_RUNSTATUS    "RUNSTATUS"

#define NUM_TASLPLANNING  8 //8个默认的波束

class DATABASESHARED_EXPORT TbTaskPlanning : public TbBase
{
public:
    TbTaskPlanning(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool add(const QList<QSqlRecord> &records);

    bool edit(const QSqlRecord record);
    bool edit(const QList<QSqlRecord> records);
    bool edit(char linkId, char status);
    bool edit(const QList<char> linkIds, char status);

    bool del();

    int  query(QList<QSqlRecord> &records);

    void initQSqlRecord(QSqlRecord &record);
private:
   //添加八个默认的波束
   bool addDefauleBeams();
};

#endif // TBLINKINFO_H
