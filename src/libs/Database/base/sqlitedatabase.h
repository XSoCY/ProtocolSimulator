#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QObject>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QVariantList>
#include "database_global.h"
#include "log.h"

// 连接数据库所需参数
struct DatabaseConnectParam
{
    QString hostName;   // 远程链接地址
    QString dbName;     // 数据库名
    QString userName;   // 用户名
    QString passwd;     // 密码
    quint32 port;       // 端口
    QString dbType;     // 连接的数据库类型，如sqlite、qodbc等
    DatabaseConnectParam()
    {
        hostName = "localhost";
        dbName = "test";
        userName = "root";
        passwd = "123456";
        port = 3306;
        dbType = "QMYSQL";
    }
};

class DATABASESHARED_EXPORT SqliteDatabase
{
public:
    explicit SqliteDatabase();
    ~SqliteDatabase();
    // 连接数据库
    bool connectDB();

    // 连接数据库
    bool connectDB(const DatabaseConnectParam &dbConnectParam);
    bool connectDB(const QString& connectionName);
    void setDbConnectParam(const DatabaseConnectParam &dbConnectParam);

    //数据库可用
    bool isSqlDataBaseValid();

    //添加数据
    /**
     * @brief insertData
     * @param tableName
     * @param rowListName
     * @param listVarData
     * @return
     */
    bool insertData(const QString& tableName,
                    const QStringList& rowListName,
                    const QVariantList& listVarData);
    bool insertData(const QString &tableName
                    , const QStringList &rowListName
                    , const QList<QVariantList> &listVarData);

    /*!
     * \brief deletData
     * \param tableName
     * \param condition
     * \return
     */
    bool deletData(const QString& tableName, const QMap<QString, QString>& conditionMap);
    //更新数据
    /*!
     * \brief updateData
     * \param tableName
     * \param updateDataMap
     * \param conditionMap
     * \param result
     * \return
     */
    int updateData(const QString& tableName, const QMap<QString, QString> &updateDataMap,
                   const QMap<QString, QString>& conditionMap);
    int updateData(const QString &tableName, const QMap<QString, QVariant> &updateDataMap,
                                   const QMap<QString, QVariant> &conditionMap);

    // 查找数据库表
    /*!
     * \brief select
     * \param tableName
     * \param selectList
     * \param conditionList
     * \param result
     * \return
     */
    int select(const QString &tableName,
               const QList<QString> &selectList,
               const QMap<QString, QString> &conditionList,
               QList<QSqlRecord> &result);
    // 关闭数据库
    void closeDB();
    // 执行sql语句
    int execQuery(const QString &query);
    //主要执行创建的sql语句
    bool Create(const QString &query);
    // 执行返回值sql语句
    int execQuery(const QString &query, QList<QSqlRecord> &result);

    int execQueryAll(const QString& tableName, QList<QSqlRecord> &records);

    bool transaction();
    bool commit();
    bool roback();

private:
    QSqlDatabase m_database;
    DatabaseConnectParam m_dbConnectParam;                                  // 数据库类型
};

#endif // SQLITEDATABASE_H
