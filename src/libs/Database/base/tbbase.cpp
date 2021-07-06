#include "tbbase.h"
#include <QDebug>

#define SELECT_SQL          "SELECT * FROM %1 "
#define SELECT_COUNT_SQL    "SELECT COUNT(*) AS DATA_COUNT FROM %1 "

#define DELETE_SQL          "DELETE FROM %1 "
#define EXIST_SQL           "SELECT * FROM DBA_TABLES WHERE OWNER='%1' AND TABLE_NAME='%2'"

#define LIMIT_SQL           "LIMIT %2, %3"
#define DATA_COUNT          "DATA_COUNT"

TbBase::TbBase(SqliteDatabase *dbbase)
    : m_dbSqliteDatabase(dbbase)
{

}

TbBase::~TbBase()
{

}

SqliteDatabase* TbBase::getDatabase()
{
    return m_dbSqliteDatabase;
}

int TbBase::getRecords(const QString& tableName
                     , const QString& swhere
                     , QList<QSqlRecord> &records)
{
    int ret = 0;

    QString selectSql = SELECT_SQL;
    selectSql = selectSql.arg(tableName);

    selectSql += swhere;

    ret = m_dbSqliteDatabase->execQuery(selectSql, records);

    return ret;
}

int TbBase::getRecords(const QString& tableName
                     , const QString& swhere
                     , PAGE_INFO &pageInfo
                     , QList<QSqlRecord> &records)
{
    int ret = 0;

    QString selectSql = SELECT_SQL;
    selectSql = selectSql.arg(tableName);

    ret = getRecords(tableName, selectSql, swhere, pageInfo, records);

    return ret;
}

int TbBase::getRecords(const QString &tableName
                       , const QList<QString> &selectList
                       , const QMap<QString, QString> &conditionList
                       , QList<QSqlRecord> &result)
{
    return m_dbSqliteDatabase->select(tableName, selectList, conditionList, result);
}

int TbBase::getDevieceStatus(QString tableName
                       , const QString &tableTime
                       , const QString &swhere
                       , QList<QSqlRecord> &records)
{
    int ret = 0;

    tableName = tableName.arg(tableTime);

    QString selectSql = SELECT_SQL;
    selectSql = selectSql.arg(tableName);
    selectSql += " ";
    selectSql += swhere;

    return m_dbSqliteDatabase->execQuery(selectSql, records);

    return ret;
}

int TbBase::getRecords(const QString &tableName
             , const QString &selectSql
             , const QString &swhere
             , PAGE_INFO &pageInfo
             , QList<QSqlRecord> &records)
{
    int icount = getDataCountForTable(tableName, swhere);
    if( icount < pageInfo.index * pageInfo.page_size ) return 0;

    pageInfo.data_count = icount;
    if( (pageInfo.data_count % pageInfo.page_size) > 0 ) pageInfo.page_count = (pageInfo.data_count/pageInfo.page_size) + 1;
    else pageInfo.page_count = (pageInfo.data_count/pageInfo.page_size);

    QString sql = selectSql;
    QString limitSql = LIMIT_SQL;
    limitSql = limitSql.arg(pageInfo.index * pageInfo.page_size).arg(pageInfo.page_size);

    sql += " ";
    sql += swhere;
    sql += " ";
    sql += limitSql;

    return m_dbSqliteDatabase->execQuery(sql, records);
}

int TbBase::getDataCountForTable(const QString& tableName, const QString& swhere)
{
    int ret = 0;
    int icount = 0;

    QString sql = SELECT_COUNT_SQL;
    sql = sql.arg(tableName);
    sql += swhere;

    QList<QSqlRecord> records;
    ret = getDatabase()->execQuery(sql, records);

    if( ret > 0 ) icount = records[0].value(DATA_COUNT).toInt();

    return icount;
}

int TbBase::del(const QString& tableName, const QString& swhere)
{
    int ret = 0;

    QString deleteSql = DELETE_SQL;
    deleteSql = deleteSql.arg(tableName);

    deleteSql += swhere;

    ret = m_dbSqliteDatabase->execQuery(deleteSql);

    return (ret >= 0);
}

bool TbBase::createTable(const QString& createTableSql, const QString& tableName)
{
    bool ret = false;

    if( isTableExist(tableName) ) return true;
    ret = m_dbSqliteDatabase->Create(createTableSql);

    return ret;
}

bool TbBase::isTableExist(const QString& tableName)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QString sql = EXIST_SQL;
    sql = sql.arg(tableName.section(".", 0, 0).replace("\"", "")).arg(tableName.section(".", 1, 1).replace("\"", ""));

    QList<QSqlRecord> records;
    int icount = getDatabase()->execQuery(sql, records);

    return (icount > 0);
}
