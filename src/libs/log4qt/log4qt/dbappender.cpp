/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/dbappender.h"
#include "log4qt/typedef.h"

#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#include <QtSql/QtSql>
#include "log4qt/layout.h"
#include "log4qt/loggingevent.h"
#include "log4qt/helpers/datetime.h"

namespace Log4Qt
{

/**************************************************************************
 * Declarations
 **************************************************************************/



/**************************************************************************
 * C helper functions
 **************************************************************************/



/**************************************************************************
 * Class implementation: WriterAppender
 **************************************************************************/

    QMap<int, QString> &CreateDBTypeMap()
    {
        static QMap<int, QString> dbTypeMap;
        dbTypeMap.insert(DBAppender::DB_Sqlite, "QSQLITE");
        return dbTypeMap;
    }

    QMap<int, QString> &g_dbTypeMap = CreateDBTypeMap();
    QAtomicInt g_connectCount(0);
    int g_flushTimeInterval(2); //flush time interval

    DBAppender::DBAppender(DBType dbType, QObject *pParent):
        AppenderSkeleton(false, pParent),
        mpEncoding(0),
        m_timeFormat("yyyy-MM-dd hh:mm:ss.zzz"),
        m_supportTranction(false),
        mImmediateFlush(false),
        m_connectName("Log4Qt_DB"),
        m_databaseHost("localhost"),
        m_tableName("log")
    {
        int count = g_connectCount.fetchAndAddOrdered(1);
        m_connectName += QString("%1").arg(count);
        m_databaseType = g_dbTypeMap[dbType];
        m_flushTimer.setInterval(g_flushTimeInterval);
        connect(&m_flushTimer, SIGNAL(timeout()), SLOT(timelyFlush()));
        m_flushTimer.start();
    }

    DBAppender::DBAppender(Layout *pLayout, DBType dbType, QObject *pParent):
        AppenderSkeleton(false, pParent),
        mpEncoding(0),
        m_timeFormat("yyyy-MM-dd hh:mm:ss.zzz"),
        m_supportTranction(false),
        mImmediateFlush(false),
        m_connectName("Log4Qt"),
        m_databaseHost("localhost"),
        m_tableName("log")
    {
        int count = g_connectCount.fetchAndAddOrdered(1);
        m_connectName += QString("%1").arg(count);
        m_databaseType = g_dbTypeMap[dbType];
        setLayout(pLayout);
        m_flushTimer.setInterval(g_flushTimeInterval);
        connect(&m_flushTimer, SIGNAL(timeout()), SLOT(timelyFlush()));
        m_flushTimer.start();
    }

    bool DBAppender::requiresLayout() const
    {
        return false;
    }

    DBAppender::~DBAppender()
    {
        close();
    }


    void DBAppender::setEncoding(QTextCodec *pEncoding)
    {
        QMutexLocker locker(&mObjectGuard);

        if (mpEncoding == pEncoding)
            return;

        mpEncoding = pEncoding;
    }

    void DBAppender::setFile(const QString &rFileName)
    {
        m_filePath = rFileName;
    }

    void DBAppender::activateOptions()
    {
        QMutexLocker locker(&mObjectGuard);
        if(!open()) return;
        if(!createTable(m_tableName)) return;
        AppenderSkeleton::activateOptions();
    }


    void DBAppender::close()
    {
        QMutexLocker locker(&mObjectGuard);

        if (isClosed())
            return;

        if(m_flushTimer.isActive())
        {
            m_flushTimer.stop();
        }
        while(m_flushTimer.isActive())
        {
            ;
        }

        if(m_database.isOpen())
        {
            if(m_supportTranction) m_database.commit();
            m_database.close();
        }

        AppenderSkeleton::close();
    }

    void DBAppender::append(const LoggingEvent &rEvent)
    {
        QMutexLocker locker(&mObjectGuard);
        if(!isOpen()) return;

        QString message;
        if(layout())
        {
            message = layout()->format(rEvent);
        }
        else
        {
            message = rEvent.message();
        }

        QString sql;
        QString tagStr;

        Level level = rEvent.level();
        switch(level.toInt())
        {
        case Level::NULL_INT:
            tagStr = TagStr::NullTag;
            break;
        case Level::ALL_INT:
            tagStr = TagStr::AllTag;
            break;
        case Level::TRACE_INT:
            tagStr = TagStr::TraceTag;
            break;
        case Level::DEBUG_INT:
            tagStr = TagStr::DebugTag;
            break;
        case Level::INFO_INT:
            tagStr = TagStr::InfoTag;
            break;
        case Level::WARN_INT:
            tagStr = TagStr::WarnTag;
            break;
        case Level::ERROR_INT:
            tagStr = TagStr::ErrorTag;
            break;
        case Level::FATAL_INT:
            tagStr = TagStr::FatalTag;
            break;
        case Level::OFF_INT:
            tagStr = TagStr::OffTag;
            break;
        default:
            tagStr = TagStr::UncapturedTag;
//            Q_ASSERT_X(false, __func__, "uncaptured log event level");
            break;
        }

        m_sqlQuery.clear();
        sql = "insert into `" + m_tableName
                + "` (" + AttrName::DateTime + "," + AttrName::Level +
                "," + AttrName::Logger + "," + AttrName::Message + ") "
                "values (:DateTime, :Level, :Logger, :Message)";
        m_sqlQuery.prepare(sql);
        m_sqlQuery.bindValue(":DateTime", DateTime::fromMilliSeconds(rEvent.timeStamp()).toString(m_timeFormat));
        m_sqlQuery.bindValue(":Level", tagStr);
        m_sqlQuery.bindValue(":Logger", rEvent.loggerName());
        m_sqlQuery.bindValue(":Message", message);
        if(!m_sqlQuery.exec())
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that sql error"
                                                        + m_sqlQuery.lastError().text()),
                                             APPENDER_ACTIVATE_SQL_ERROR);
            e << name();
            logger()->error(e);
            return;
        }

        if (handleIoErrors())
            return;

        if (immediateFlush())
        {
            if(m_supportTranction)
            {
                m_database.commit();
                m_database.transaction();
            }
            if (handleIoErrors())
                return;
        }
        return;
    }

    bool DBAppender::checkEntryConditions() const
    {
        if(!isOpen())
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that database cannot open:" + m_database.lastError().text()),
                                             APPENDER_ACTIVATE_DBOPEN_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }
        return AppenderSkeleton::checkEntryConditions();
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug DBAppender::debug(QDebug &rDebug) const
    {
        QString layout_name;
        if (layout())
            layout_name = layout()->name();
        QString codec_name;
        if (encoding())
            codec_name = QLatin1String(encoding()->name());

        rDebug.nospace() << "DBAppender("
            << "name:" << name() << " "
            << "encoding:" << codec_name << " "
            << "filter:" << firstFilter()
            << "immediateFlush:" << immediateFlush()
            << "isactive:" << isActive()
            << "isclosed:" << isClosed()
            << "layout:" << layout_name
            << "referencecount:" << referenceCount() << " "
            << "threshold:" << threshold().toString()
            << ")";
        return rDebug.space();
    }
#endif // QT_NO_DEBUG_STREAM


    bool DBAppender::handleIoErrors() const
    {
        return false;
    }


    void DBAppender::writeFooter() const
    {
        return;
    }


    void DBAppender::writeHeader() const
    {
        return;
    }

    void DBAppender::timelyFlush()
    {
        if(isOpen() && m_supportTranction)
        {
            m_database.commit();
            m_database.transaction();
        }
    }

    bool DBAppender::open()
    {
        if(isOpen())
        {
            return true;
        }

        if(m_filePath.isEmpty())
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that requires db file"),
                                             APPENDER_ACTIVATE_MISSING_FILE_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }

        if(!QSqlDatabase::isDriverAvailable(m_databaseType))
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that requires sql driver"),
                                             APPENDER_ACTIVATE_MISSING_DBDRIVER_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }

        m_database = QSqlDatabase::addDatabase(m_databaseType, m_connectName);
        if (!m_database.isValid())
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that database is invalid:" + m_database.lastError().text()),
                                             APPENDER_ACTIVATE_DBINVALID_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }
        m_database.setHostName(m_databaseHost);
        m_database.setDatabaseName(m_filePath);

        if (!m_database.open())
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that database cannot open:" + m_database.lastError().text()),
                                             APPENDER_ACTIVATE_DBOPEN_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }
        m_sqlQuery = QSqlQuery(m_database);

        if(m_database.driver()->hasFeature(QSqlDriver::Transactions))
        {
            m_supportTranction = true;
            m_database.transaction();
        }
        return true;
    }

    bool DBAppender::isOpen() const
    {
        return m_database.isOpen();
    }

    bool DBAppender::createTable(const QString &table)
    {
        Q_ASSERT(isOpen());
        QString sql;
        m_sqlQuery.clear();
        sql = "create table if not exists `" + table
                + "` (`id` INTEGER PRIMARY KEY AUTOINCREMENT "
                  ",`" + AttrName::DateTime + "` CHAR(25) NOT NULL"
                  ",`" + AttrName::Level + "` CHAR(10) NOT NULL"
                  ",`" + AttrName::Logger + "` CHAR(30) NOT NULL"
                  ",`" + AttrName::Message + "` TEXT)";
        if(!m_sqlQuery.exec(sql))
        {
            LogError e = LOG4QT_QCLASS_ERROR(QT_TR_NOOP("Activation of Appender '%1' that sql exec fail:"
                                                        + m_sqlQuery.lastError().text()),
                                             APPENDER_ACTIVATE_SQL_ERROR);
            e << name();
            logger()->error(e);
            return false;
        }
        return true;
    }



    /******************************************************************************
     * Implementation: Operators, Helper
     ******************************************************************************/


} // namespace Log4Qt

