#ifndef LOG_H
#define LOG_H

#include "log_global.h"

#define LOG_DATA_FORMAT()    QString("FILE: ") + QString(__FILE__) + QString(" FUNCTION: ") + __FUNCTION__  \
                                        + QString(" LINE: ") + QString::number(__LINE__)
enum Log_Level
{
    LOG_LEVEL_PROMPT    = 1, //提示
    LOG_LEVEL_WARNING   = 2, //告警
    LOG_LEVEL_ERROR     = 3, //错误
};

class LOGSHARED_EXPORT Log
{
public:
    static Log *getInstance()
    {
        if( !m_log ) m_log = new Log();

        return m_log;
    }

    int writeLog(ushort objectID, Log_Level level, QString strMsg);

    /**
     * @brief writeLog  写日志
     * @param level     日志级别 1：提示 2：告警 3：错误
     * @param msgHead   日志头（记录文件、函数、行）
     * @param strMsg    自定义日志体
     * @return
     */
    int writeLog(Log_Level level, QString msgHead, QString strMsg);
private:
    Log();

private:
    static Log *m_log;
};

#endif // LOG_H
