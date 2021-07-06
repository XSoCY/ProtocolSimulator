#ifndef TBBASE_H
#define TBBASE_H

#include "database_global.h"
#include "sqlitedatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

#define TBBASE_DEL_SQL "DELETE FROM %1 "

typedef struct str_page_info
{
    //页码
    ushort index = 0;
    //页大小
    ushort page_size = 50;
    //总页数
    ushort page_count = 0;
    //总数据量
    int data_count = 0;

}PAGE_INFO, *PPAGE_INFO;


class DATABASESHARED_EXPORT TbBase
{
public:
    TbBase(SqliteDatabase *dbbase);
    ~TbBase();

    /**
     * @brief getDatabase 获取当前数据库连接
     * @return SqliteDatabase指针
     */
    SqliteDatabase* getDatabase();

    /**
     * @brief getRecords 获取满足条件的数据
     * @param tableName 要查询的表名称
     * @param swhere 查询条件：需要自己带 "WHERE" 关键字
     * @return 查询出来的数据
     */
    int getRecords(const QString& tableName
                 , const QString& swhere
                 , QList<QSqlRecord> &records);

    /**
     * @brief getRecords 分页获取满足条件的数据
     * @param tableName 要查询的表名称
     * @param swhere 查询条件：需要自己带 "WHERE" 关键字
     * @param pageInfo 分页信息
     * @return 查询出来的数据
     */
    int getRecords(const QString& tableName
                 , const QString& swhere
                 , PAGE_INFO &pageInfo
                 , QList<QSqlRecord> &records);

    /**
     * @brief getRecords    获取满足条件的数据
     * @param tableName     要查询的表名称
     * @param selectList    字段名列表
     * @param conditionList 条件列表
     * @param result        查询出来的数据
     * @return 查到的记录条数
     */
    int getRecords(const QString &tableName,
                   const QList<QString> &selectList,
                   const QMap<QString, QString> &conditionList,
                   QList<QSqlRecord> &result);
    /**
     * @brief getRecords 设备状态获取满足条件的数据
     * @param tableName 要查询的表名称
     * @param tableTime 要查询的表名称末尾的时间
     * @param swhere 查询条件：需要自己带 "WHERE" 关键字
     * @return 查询出来的数据
     */
    int getDevieceStatus(QString tableName
                 ,  const QString& tableTime
                 , const QString& swhere
                 , QList<QSqlRecord> &records
                 );

    /**
     * @brief getRecords 分页获取满足条件的数据
     * @param selectSql sql语句
     * @param pageInfo 分页信息
     * @return 查询出来的数据
     */
    int getRecords(const QString &tableName
                   , const QString &selectSql
                   , const QString &swhere
                   , PAGE_INFO &pageInfo
                   , QList<QSqlRecord> &records);

    /**
     * @brief getDataCountForTable 获取表中满足条件的数据量
     * @param tableName 要查询的表名称
     * @param swhere 查询条件：需要自己带 "WHERE" 关键字
     * @return 满足条件的数据量
     */
    int getDataCountForTable(const QString& tableName, const QString& swhere);

    /**
     * @brief del 删除数据
     * @param tableName 要删除数据的表名称
     * @param swhere 查询条件：需要自己带 "WHERE" 关键字
     * @return 删除数据的行数
     */
    int del(const QString& tableName
                 , const QString& swhere);

    /**
     * @brief createTable 创建表
     * @param tableName 创建的表名称
     * @return true-成功；false-失败；
     */
    bool createTable(const QString& createTableSql, const QString& tableName);

    /**
     * @brief isTableExist 判断表是否存在
     * @param tableName 表名称
     * @return true-成功；false-失败；
     */
    bool isTableExist(const QString& tableName);

private:
    SqliteDatabase *m_dbSqliteDatabase;
};

#endif // TBBASE_H
