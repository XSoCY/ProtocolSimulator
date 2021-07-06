#ifndef AUTOTESTSTANDARD_H
#define AUTOTESTSTANDARD_H
#include <QJsonObject>

#include "tbbase.h"

#define CREATE_TABLE_AUTOTESTSTAND_SQL   "CREATE TABLE \"DMBMonitor\".\"AUTOTESTSTAND\" \
                                    ( \
                                    \"TESTTYPE\" VARCHAR(256) , \
                                    \"TIME\" TIMESTAMP(6), \
                                    \"BASEDATA\" BLOB, \
                                    \"RESERVE\" BLOB) STORAGE(ON \"MAIN\", CLUSTERBTR) ;"

#define TABLE_NAME_AUTOTESTSTAND     "\"DMBMonitor\".\"AUTOTESTSTAND\""

#define AUTOTEST_FIELD_STANDTESTTYPE         "TESTTYPE"
#define AUTOTEST_FIELD_STANDTIME             "TIME"
#define AUTOTEST_FIELD_STANDDATA             "BASEDATA"
#define AUTOTEST_FIELD_STANDRESERVE          "RESERVE"
namespace AutotestDbDefinition
{
const QString s_timeBaseformatField = "yyyy-MM-dd hh:mm:ss"; // 设备存储时间格式

}
class DATABASESHARED_EXPORT AutoTestStandard : public TbBase
{
public:
    AutoTestStandard(SqliteDatabase *dbbase);

public:
    bool creatTable();

    void initRecord(QSqlRecord& initRecord);
    //初始化表，默认创建几个的记录
    bool addDefaultRecord(const QStringList &testName);

    //修改数据
    bool editOneTestData(QSqlRecord& record);
    //查询数据
    int  query(const QString& testTypeName, QList<QSqlRecord> &records);

private:
    bool addRecord(const QSqlRecord& record);
    bool delRecord(const QSqlRecord& record);
};

#endif // AUTOTESTSTANDARD_H
