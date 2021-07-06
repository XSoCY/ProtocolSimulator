#ifndef AUTOTESTRESULT_H
#define AUTOTESTRESULT_H
#include <QJsonObject>

#include "tbbase.h"

#define CREATE_TABLE_AUTOTEST_SQL   "CREATE TABLE \"DMBMonitor\".\"AUTOTEST\" \
                                    ( \
                                    \"TESTTYPE\" VARCHAR(256) , \
                                    \"TIME\" TIMESTAMP(6), \
                                    \"PARADATA\" BLOB, \
                                    \"RESULTDATA\" BLOB, \
                                    \"RESERVE\" BLOB) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define TABLE_NAME_AUTOTEST     "\"DMBMonitor\".\"AUTOTEST\""

#define AUTOTEST_FIELD_TESTTYPE         "TESTTYPE"
#define AUTOTEST_FIELD_TIME             "TIME"
#define AUTOTEST_FIELD_PARAMDATA         "PARADATA"
#define AUTOTEST_FIELD_RESULTDATA       "RESULTDATA"
#define AUTOTEST_FIELD_RESERVE          "RESERVE"


namespace AutotestDbDefinition
{
const QString s_timeformatField = "yyyy-MM-dd hh:mm:ss"; // 设备存储时间格式

}

class DATABASESHARED_EXPORT AutotestResult : public TbBase
{
public:
    AutotestResult(SqliteDatabase *dbbase);

public:
    bool creatTable();

    void initRecord(QSqlRecord& initRecord);
    //初始化表，默认创建几个的记录
    bool addDefaultRecord(const QStringList &testName);
    //添加记录
    bool addRecord(const QSqlRecord& record);

    //修改数据
    bool editOneTestData(QSqlRecord& record);
    //查询数据
    int  query(const QString& testTypeName, QList<QSqlRecord> &records);
    int queryCondition(const QString& queryCondition, QList<QSqlRecord>& records);
private:
    bool delRecord(const QSqlRecord& record);

private:



};

#endif // AUTOTESTRESULT_H
