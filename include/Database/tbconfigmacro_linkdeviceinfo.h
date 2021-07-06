#ifndef TBCONFIGMACRO_LINKDEVICEINFO_H
#define TBCONFIGMACRO_LINKDEVICEINFO_H

#include "tbbase.h"

#define CREATE_TABLE_CONFIGMACRO_LINKDEVICE_SQL     "CREATE TABLE \"DMBMonitor\".\"CONFIGMACRO_LINKDEVICEINFO\" \
                                                    ( \
                                                    \"DEV_ID\" INT NOT NULL, \
                                                    \"CM_ID\" INT NOT NULL, \
                                                    NOT CLUSTER PRIMARY KEY(\"DEV_ID\", \"CM_ID\")) STORAGE(ON \"MAIN\", CLUSTERBTR) ; "

#define CONFIGMACRO_LINKDEVICE_SELECT_SQL           "SELECT * FROM %1 "
#define CONFIGMACRO_LINKDEVICE_DELETE_SQL           "DELETE FROM %1 "
#define TABLE_NAME_CONFIGMACRO_LINK_DEVICE          "\"DMBMonitor\".\"CONFIGMACRO_LINKDEVICEINFO\""

#define CONFIGMACRO_LINKDEVICE_FIELD_DEV_ID         "DEV_ID"
#define CONFIGMACRO_LINKDEVICE_FIELD_CM_ID          "CM_ID"

#define CONFIGMACRO_LINKDEVICE_FIELD_NAME           "NAME"
#define CONFIGMACRO_LINKDEVICE_FIELD_DESCRIPTION    "DESCRIPTION"
#define CONFIGMACRO_LINKDEVICE_FIELD_SUBSYS         "SUBSYS"
#define CONFIGMACRO_LINKDEVICE_FIELD_SUBSYSSN       "SUBSYSSN"
#define CONFIGMACRO_LINKDEVICE_FIELD_ISMAIN         "ISMAIN"
#define CONFIGMACRO_LINKDEVICE_FIELD_OBJECTNAME     "OBJECTNAME"

class DATABASESHARED_EXPORT TbConfigMacro_LinkDeviceInfo : public TbBase
{
public:
    TbConfigMacro_LinkDeviceInfo(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const QSqlRecord &record);
    bool del(const QSqlRecord &record);
    bool del(ulong configMacroId);
    bool edit(const QSqlRecord &record);
    int  query(QList<QSqlRecord> &records, str_page_info &pageInfo);
    int  queryForMacroId(uint macroId, QList<QSqlRecord> &records);
    void initQSqlRecord(QSqlRecord &record);
};

#endif // TBCONFIGMACRO_LINKDEVICEINFO_H
