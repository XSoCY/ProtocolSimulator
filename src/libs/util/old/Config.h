#ifndef CONFIG_H
#define CONFIG_H
#include "util_global.h"

#include "Singleton.h"

class QString;
class QStringList;
class Json;

/**
 * 用于读写配置文件:
 * 1. resources/config.json: 存储配置的信息，例如数据库信息，QSS 文件的路径
 */
#define ConfigInstance Singleton<Config>::getInstance()

class UTILSHARED_EXPORT Config
{
    SINGLETON(Config)
public:
    void destroy();
    QString getDatabaseType() const;
    QString getDatabaseHost() const;
    QString getDatabaseName() const;
    QString getDatabaseUsername() const;
    QString getDatabasePassword() const;
    QString getDatabaseTestOnBorrowSql() const;
    bool getDatabaseTestOnBorrow() const;
    int getDatabaseMaxWaitTime() const;
    int getDatabaseMaxConnectionCount() const;
    int getDatabasePort() const;
    bool isDatabaseDebug() const;
    int getLogMaxShowCount() const;
    int getClockRowCount() const;
    void getDeviceId(QStringList& idList, QStringList& nameList);
    QStringList getDatabaseSqlFiles() const;

    QStringList getQssFiles() const;

private:
    Json* json;
};

#endif  // CONFIG_H
