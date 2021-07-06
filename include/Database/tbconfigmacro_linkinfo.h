#ifndef TBCONFIGMACRO_LINKINFO_H
#define TBCONFIGMACRO_LINKINFO_H

#include "tbbase.h"

#define CREATE_TABLE_CONFIGMACRO_LINKINFO_SQL   "CREATE TABLE \"DMBMonitor\".\"CONFIGMACRO_LINKINFO\" \
                                                ( \
                                                \"L_ID\" INT NOT NULL, \
                                                \"CM_ID\" INT NOT NULL, \
                                                \"NAME\" VARCHAR(32), \
                                                \"DESCRIPTION\" VARCHAR(128), \
                                                CLUSTER PRIMARY KEY(\"L_ID\", \"CM_ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ; "

#define CONFIGMACRO_LINKINFO_SELECT_SQL         "SELECT * FROM %1 "
#define CONFIGMACRO_LINKINFO_DELETE_SQL         "DELETE FROM %1 "
#define TABLE_NAME_CONFIGMACRO_LINKINFO         "\"DMBMonitor\".\"CONFIGMACRO_LINKINFO\""

#define CONFIGMACRO_LINKINFO_FIELD_L_ID         "L_ID"
#define CONFIGMACRO_LINKINFO_FIELD_CM_ID        "CM_ID"
#define CONFIGMACRO_LINKINFO_FIELD_NAME         "NAME"
#define CONFIGMACRO_LINKINFO_FIELD_DESCRIPTION  "DESCRIPTION"

class DATABASESHARED_EXPORT TbConfigMacro_LinkInfo : public TbBase
{
public:
    TbConfigMacro_LinkInfo(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool del(const QSqlRecord &record);
    bool edit(const QSqlRecord &record);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
};

#endif // TBCONFIGMACRO_LINKINFO_H
