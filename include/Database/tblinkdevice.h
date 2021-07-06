#ifndef TBLINKDEVICE_H
#define TBLINKDEVICE_H

#include "tbbase.h"

#define CREATE_TABLE_LINKDEVICE_SQL     "CREATE TABLE \"DMBMonitor\".\"LINKDEVICE\" \
                                        ( \
                                        \"LINK_ID\" INT NOT NULL, \
                                        \"DEV_TYPE\" INT NOT NULL, \
                                        \"DEV_ID\" INT NOT NULL, \
                                        \"DEV_SN\" INT NOT NULL, \
                                        CLUSTER PRIMARY KEY(\"LINK_ID\", \"DEV_TYPE\", \"DEV_ID\", \"DEV_SN\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ; "

#define LINKDEVICE_SELECT_SQL           "SELECT * FROM %1 "
#define LINKDEVICE_DELETE_SQL           "DELETE FROM %1 "
#define TABLE_NAME_LINKDEVICE           "\"DMBMonitor\".\"LINKDEVICE\""

#define LINKDEVICE_FIELD_LINK_ID        "LINK_ID"
#define LINKDEVICE_FIELD_DEV_TYPE       "DEV_TYPE"
#define LINKDEVICE_FIELD_DEV_ID         "DEV_ID"
#define LINKDEVICE_FIELD_DEV_SN         "DEV_SN"

class DATABASESHARED_EXPORT TbLinkDevice : public TbBase
{
public:
    TbLinkDevice(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool add(const QList<QSqlRecord> &records);

    bool del();
    bool del(const QSqlRecord &record);
    bool del(const char &linkId);
    bool del(const QList<char> &linkIds);

    bool edit(const char linkId, const QList<QSqlRecord> &records);
    bool edit(const QList<QSqlRecord> &records);

    int  query(QList<QSqlRecord> &records);
    int  queryForLinkId(char linkId, QList<QSqlRecord> &records);

    void initQSqlRecord(QSqlRecord &record);
};

#endif // TBDEVICEINFO_H
