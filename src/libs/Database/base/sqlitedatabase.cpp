#include "sqlitedatabase.h"
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#define TABLE_EXSIT_SQL  "SELECT 1 FROM sys_class WHERE RELNAME='%1' AND RELKIND='r'"

SqliteDatabase::SqliteDatabase()
{

}

SqliteDatabase::~SqliteDatabase()
{

}

bool SqliteDatabase::connectDB()
{
    if( m_dbConnectParam.dbType == "QODBC" )
    {
        m_database = QSqlDatabase::addDatabase("QODBC");

        m_database.setHostName(m_dbConnectParam.hostName);
        m_database.setPort(m_dbConnectParam.port);
        m_database.setDatabaseName(m_dbConnectParam.dbName);
        m_database.setUserName(m_dbConnectParam.userName);
        m_database.setPassword(m_dbConnectParam.passwd);
    }

    bool ok = m_database.open();

    if( !ok )
    {
        QStringList str;
        str << "connect database error: "
            << "hostName:" + m_dbConnectParam.hostName
            << "port:" + QString::number(m_dbConnectParam.port)
            << "dbName:" + m_dbConnectParam.dbName
            << "userName:" + m_dbConnectParam.userName
            << "passwd:" << m_dbConnectParam.passwd
            << "dbtype:" + m_dbConnectParam.dbType;

        str << m_database.lastError().text();

        Log::getInstance()->getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), str.join(", "));
    }

    return ok;
}

bool SqliteDatabase::connectDB(const DatabaseConnectParam &dbConnectParam)
{
    setDbConnectParam(dbConnectParam);

    return connectDB();
}

bool SqliteDatabase::connectDB(const QString &connectionName)
{
    if( m_dbConnectParam.dbType == "QODBC" )
    {
        m_database = QSqlDatabase::addDatabase("QODBC", connectionName);

        m_database.setHostName(m_dbConnectParam.hostName);
        m_database.setPort(m_dbConnectParam.port);
        m_database.setDatabaseName(m_dbConnectParam.dbName);
        m_database.setUserName(m_dbConnectParam.userName);
        m_database.setPassword(m_dbConnectParam.passwd);
    }

    bool ok = m_database.open();

    if( !ok )
    {
        QStringList str;
        str << "connect database error: "
            << "hostName:" + m_dbConnectParam.hostName
            << "port:" + QString::number(m_dbConnectParam.port)
            << "dbName:" + m_dbConnectParam.dbName
            << "userName:" + m_dbConnectParam.userName
            << "passwd:" << m_dbConnectParam.passwd
            << "dbtype:" + m_dbConnectParam.dbType;

        str << m_database.lastError().text();

        Log::getInstance()->getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), str.join(", "));
    }

    return ok;
}

void SqliteDatabase::setDbConnectParam(const DatabaseConnectParam &dbConnectParam)
{
    m_dbConnectParam.hostName      = dbConnectParam.hostName;
    m_dbConnectParam.dbName        = dbConnectParam.dbName  ;
    m_dbConnectParam.userName      = dbConnectParam.userName;
    m_dbConnectParam.passwd        = dbConnectParam.passwd  ;
    m_dbConnectParam.port          = dbConnectParam.port    ;
    m_dbConnectParam.dbType        = dbConnectParam.dbType  ;
}

bool SqliteDatabase::isSqlDataBaseValid()
{
    bool retFlag = false;

    retFlag = m_database.isValid();

    return retFlag;
}

bool SqliteDatabase::insertData(const QString &tableName
                                , const QStringList &rowListName
                                , const QVariantList &listVarData)
{
    if ( !m_database.isValid() ) return false;

    if ( !m_database.isOpen() && !m_database.open() )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return false;
    }

    bool result = false;
    QString strQuery = QString("INSERT INTO ") + tableName;
    //添加列名
    int icount = rowListName.size();
    QString strRowNames;
    QString strValues;
    for(int i=0; i<icount; ++i)
    {
        if( i < icount -1 ) strRowNames +=  rowListName[i] + QString(",");
        else strRowNames +=  rowListName[i];

        if( i < icount -1 ) strValues += QString("?, ");
        else strValues += QString("?");
    }

    strQuery += "(" + strRowNames + ") ";
    strQuery += "VALUES (" + strValues + ")";

    //添加数据
    QSqlQuery query(m_database);
    result = query.prepare(strQuery);
    if(!result)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(strQuery).arg(query.lastError().text()));
        return result;
    }

    //绑定数据
    for(int i = 0; i<icount; ++i)
    {
        query.bindValue(i, listVarData.at(i));
    }

    result = query.exec();
    if( !result )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("query.exec error:%1").arg(query.lastError().text()));
        return result;
    }

    return result;
}

bool SqliteDatabase::insertData(const QString &tableName,
                                const QStringList &rowListName,
                                const QList<QVariantList> &listVarData)
{
    if ( !m_database.isValid() ) return false;

    if ( !m_database.isOpen() && !m_database.open() )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return false;
    }

    bool result = false;
    QString strQuery = QString("INSERT INTO ") + tableName;
    //添加列名
    int icount = rowListName.size();
    QString strRowNames;
    QString strValues;
    for(int i=0; i<icount; ++i)
    {
        if( i < icount -1 ) strRowNames +=  rowListName[i] + QString(",");
        else strRowNames +=  rowListName[i];
    }
    int valueCount =listVarData.size();
    for(int i =0 ; i < valueCount; i++)
    {
        if( i < valueCount -1 ) strValues += QString("?, ");
        else strValues += QString("?");
    }
    strQuery += "(" + strRowNames + ") ";
    strQuery += "VALUES (" + strValues + ")";

    //添加数据
    QSqlQuery query(m_database);
    result = query.prepare(strQuery);
    if(!result)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(strQuery).arg(query.lastError().text()));
        return result;
    }

    //绑定数据
    for(int rowIndex =0; rowIndex < listVarData.size(); rowIndex++)
    {
        query.addBindValue(listVarData[rowIndex]);
    }
    result = query.execBatch();
    if( !result )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("query.exec error:%1").arg(query.lastError().text()));
        return result;
    }

    return result;
}

bool SqliteDatabase::deletData(const QString &tableName,
                               const QMap<QString, QString> &conditionMap)
{
    bool ret = false;
    QString query("DELETE FROM ");
    query += tableName;

    //条件删除
    QMapIterator<QString, QString> iter(conditionMap);
    if (iter.hasNext())
    {
        query += " WHERE";
    }
    while (iter.hasNext()) {
        iter.next();
        query += QString(" %1 = '%2'").arg(iter.key()).arg(iter.value());
        query += " AND";
    }
    if (query.endsWith("AND"))
    {
        query.remove(query.length() - 3, 3);
        query = query.trimmed();
    }

    int retCount = execQuery(query);
    ret = (retCount == -1) ? false : true;
    return ret;
}

int SqliteDatabase::updateData(const QString &tableName, const QMap<QString, QString> &updateDataMap,
                               const QMap<QString, QString> &conditionMap)
{
    if (updateDataMap.isEmpty()) return -1;
    if ( !m_database.isValid() ) return -1;

    if ( !m_database.isOpen() && !m_database.open() )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return -1;
    }

    QString strquery("UPDATE ");
    strquery += tableName;
    strquery += " SET ";

    {
        //更新的数据
        QMapIterator<QString, QString> iterUpdate(updateDataMap);
        while (iterUpdate.hasNext()) {
            iterUpdate.next();
            strquery += QString(" %1 = ?,").arg(iterUpdate.key()).arg(iterUpdate.value());
        }
        if(strquery.endsWith(","))
        {
            strquery.remove(strquery.length() - 1, 1);
            strquery.trimmed();
        }

    }

    //条件更新
    QMapIterator<QString, QString> iter(conditionMap);
    if (iter.hasNext())
    {
        strquery += " WHERE";
    }
    while (iter.hasNext())
    {
        iter.next();
        strquery += QString(" %1 = '%2'").arg(iter.key()).arg(iter.value());
        strquery += " AND";
    }
    if (strquery.endsWith("AND"))
    {
        strquery.remove(strquery.length() - 3, 3);
        strquery = strquery.trimmed();
    }

    QSqlQuery query(m_database);
    bool retFlag = query.prepare(strquery);
    if(!retFlag)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(strquery).arg(query.lastError().text()));
        return -1;
    }
    //绑定数据
    if( strquery.endsWith(",") )
    {
        strquery.remove(strquery.length() - 1, 1);
        strquery.trimmed();
    }
    int indexData = 0;
    QMapIterator<QString, QString> iterUpdate(updateDataMap);
    while (iterUpdate.hasNext())
    {
        iterUpdate.next();
        query.bindValue(indexData, iterUpdate.value());
        ++indexData;
    }

    retFlag = query.exec();
    if(!retFlag)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("query.exec error:%1").arg(query.lastError().text()));
        return -1;
    }

    return 0;
}


int SqliteDatabase::updateData(const QString &tableName
                               , const QMap<QString, QVariant> &updateDataMap,
                               const QMap<QString, QVariant> &conditionMap)
{
    if (updateDataMap.isEmpty()) return -1;
    if ( !m_database.isValid() ) return -1;

    if ( !m_database.isOpen() && !m_database.open() )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return -1;
    }

    QString strquery("UPDATE ");
    strquery += tableName;
    strquery += " SET ";

    if( updateDataMap.size() > 0)
    {
        //更新的数据
        QMap<QString, QVariant>::const_iterator iterUpdate;
        for (iterUpdate=updateDataMap.begin(); iterUpdate!=updateDataMap.end(); ++iterUpdate)
        {
            strquery += QString(" %1=?").arg(iterUpdate.key());
            if(iterUpdate != (updateDataMap.end()-1)) strquery += QString(" ,").arg(iterUpdate.key());
        }
    }
    else return -1;

    //条件更新
    if( conditionMap.size() > 0 )
    {
        strquery += " WHERE";
        QMap<QString, QVariant>::const_iterator iterWhere;
        for (iterWhere=conditionMap.begin(); iterWhere!=conditionMap.end(); ++iterWhere)
        {
            strquery += QString(" %1=?").arg(iterWhere.key());
            if(iterWhere != (conditionMap.end()-1)) strquery += " AND";
        }
    }

    QSqlQuery query(m_database);

    bool retFlag = query.prepare(strquery);
    if(!retFlag)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(strquery).arg(query.lastError().text()));
        return -1;
    }
    //绑定数据
    int indexData = 0;
    QMapIterator<QString, QVariant> iterBUpdate(updateDataMap);
    while (iterBUpdate.hasNext())
    {
        iterBUpdate.next();
        query.bindValue(indexData, iterBUpdate.value());
        ++indexData;
    }

    QMapIterator<QString, QVariant> iterBWhere(conditionMap);
    while (iterBWhere.hasNext())
    {
        iterBWhere.next();
        query.bindValue(indexData, iterBWhere.value());
        ++indexData;
    }

    retFlag = query.exec();
    if( !retFlag )
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("query.exec error:%1").arg(query.lastError().text()));
        return -1;
    }

    return 0;
}

int SqliteDatabase::select(const QString &tableName,
                           const QList<QString> &selectList,
                           const QMap<QString, QString> &conditionList,
                           QList<QSqlRecord> &result)
{
    QString query("SELECT ");
    if (selectList.isEmpty())
    {
        query += "* ";
    }
    else
    {
        foreach (auto item, selectList)
        {
            query += item;
            query += ", ";
        }
        if (query.endsWith(", "))
        {
            query.remove(query.length() - 2, 1);
        }
    }
    query += "FROM ";
    query += tableName;
    QMapIterator<QString, QString> iter(conditionList);
    if (iter.hasNext())
    {
        query += " WHERE";
    }
    while (iter.hasNext()) {
        iter.next();
        query += QString(" %1 = '%2'").arg(iter.key()).arg(iter.value());
        query += " AND";
    }
    if (query.endsWith("AND"))
    {
        query.remove(query.length() - 3, 3);
        query = query.trimmed();
    }

    execQuery(query, result);
    return result.count();
}

void SqliteDatabase::closeDB()
{
    if (m_database.isOpen())
    {
        m_database.close();
    }
}

bool SqliteDatabase::Create(const QString &sqlQuery)
{
    bool ret = false;
    if (!m_database.isValid()) return false;

    if ((!m_database.isOpen()) && (!m_database.open()))
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return false;
    }

    QSqlQuery query(m_database);
    try
    {
        if ( !query.prepare(sqlQuery) )
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(sqlQuery).arg(query.lastError().text()));
            return false;
        }

        ret = query.exec(sqlQuery);
    }
    catch(...)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database error:%1 - %2").arg(sqlQuery).arg(m_database.lastError().text()));
    }

    return ret;
}

int SqliteDatabase::execQuery(const QString &query)
{
    int rows = 0;
    if (!m_database.isValid())
    {
        return -1;
    }
    if ((!m_database.isOpen()) && (!m_database.open()))
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return -1;
    }

    QSqlQuery sqlQuery(m_database);
    try
    {
        if (sqlQuery.prepare(query))
        {
            sqlQuery.exec(query);
        }

        rows = sqlQuery.numRowsAffected();

        if (query.startsWith("insert", Qt::CaseInsensitive))
        {
            if (rows > 0) rows = sqlQuery.lastInsertId().toInt();
            else rows = 0;
        }
    }
    catch(...)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database error:%1 - %2").arg(query).arg(m_database.lastError().text()));
    }

    return rows;
}

int SqliteDatabase::execQuery(const QString &query, QList<QSqlRecord> &result)
{
    int rows = 0;

    if (!m_database.isValid()) return -1;
    if ((!m_database.isOpen()) && (!m_database.open()))
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database open error: %1").arg(m_database.lastError().text()));
        return -1;
    }

    QSqlQuery sqlQuery(m_database);
    try
    {
        sqlQuery.setForwardOnly(true);

        if (sqlQuery.prepare(query))
        {
            sqlQuery.exec(query);
        }
        else
        {
            Log::getInstance()->writeLog(LOG_LEVEL_ERROR , LOG_DATA_FORMAT(), QString("query prepare error: %1 - %2").arg(query).arg(sqlQuery.lastError().text()));
        }

        while(sqlQuery.next())
        {
            result.append(sqlQuery.record());
        }

        rows = result.count();
    }
    catch(...)
    {
        Log::getInstance()->writeLog(LOG_LEVEL_ERROR, LOG_DATA_FORMAT(), QString("database error:%1 - %2").arg(query).arg(m_database.lastError().text()));
    }

    return rows;
}

int SqliteDatabase::execQueryAll(const QString& tableName, QList<QSqlRecord> &records)
{
    QString sql = "SELECT * FROM %1";
    sql = sql.arg(tableName);

    return execQuery(sql, records);
}

bool SqliteDatabase::transaction()
{
    return m_database.transaction();
}

bool SqliteDatabase::commit()
{
    return m_database.commit();
}

bool SqliteDatabase::roback()
{
    return m_database.rollback();
}

