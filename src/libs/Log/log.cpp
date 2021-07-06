#include "log.h"

#ifdef PLATFORM_LXTSSP
    #include "LxTsspCommonDefinition.h"
#endif

#include <QDebug>

Log *Log::m_log;

Log::Log()
{
}

#ifdef PLATFORM_LXTSSP
int Log::writeLog(ushort objectID, Log_Level level, QString strMsg)
{
    ILxTsspLogManager* pLogMgr = LxTsspObjectManager::Instance()->GetLogManager();
    if(pLogMgr != NULL)
    {
        TLxTsspLog log;
        memset(&log, 0, sizeof(log));
        /// 日志记录时的时间，由日志管理模块统一填写，采用计算机时间还是时统时间？
        //time_t time;
        /// 登录用户的名称
        //char szUserName[16];
        /// 日志来源，使用设备号表示
        //uint uiSource;
        /// 对象标识；对象管理器使用的标识
        strcpy(log.szObjectID, QByteArray((char*)&objectID, sizeof(ushort)).toHex().data());
        /// 日志生成者类别。平台对象生成的日志信息可以不对用户展示。
        /// 平台对象(1)、应用对象(2)、其他待定
        log.ucSrcType = 2;
        /// 下面3项可由具体项目定义
        /// 警告级别
        /// 提示(1)、告警(2)、错误(3)
        log.ucWarningLevel = level;
        /// 主类型
        /// 分为用户操控(1)和设备工作(2)
        log.ucMainType = 1;
        /// 子类型
        /// 用户操控的子类型分为：0x001--界面操作；0x002--用户管理；
        /// 设备工作的子类型分为：0x001--设备状态；0x002--内部接口；0x003--外部部接口；
        log.ucSubType = 1;
        /// 日志内容
        strcpy(log.szContent, strMsg.toUtf8().data());

        pLogMgr->Add(log);

        return 1;
    }

    return -1;
}

/**
 * @brief writeLog  写日志
 * @param level     日志级别 1：提示 2：告警 3：错误
 * @param msgHead   日志头（记录文件、函数、行）
 * @param strMsg    自定义日志体
 * @return
 */
int Log::writeLog(Log_Level level, QString msgHead, QString strMsg)
{
    QString strLog;
    switch(level)
    {
        case LOG_LEVEL_PROMPT:
        strLog = msgHead + QString("提示：") + strMsg;
        break;
        case LOG_LEVEL_WARNING:
        strLog = msgHead + QString("警告：") + strMsg;
        break;
        case LOG_LEVEL_ERROR:
        strLog = msgHead + QString("错误：") + strMsg;
        break;
    }
    qDebug() << strLog;
    return 1;

    ILxTsspLogManager* pLogMgr = LxTsspObjectManager::Instance()->GetLogManager();
    if(pLogMgr != NULL)
    {
        TLxTsspLog log;
        memset(&log, 0, sizeof(log));

        /// 日志记录时的时间，由日志管理模块统一填写，采用计算机时间还是时统时间？
        //time_t time;
        /// 登录用户的名称
        //char szUserName[16];
        /// 日志来源，使用设备号表示
        //uint uiSource;
        /// 对象标识；对象管理器使用的标识
        //strcpy(log.szObjectID, QByteArray((char*)&objectID, sizeof(ushort)).toHex().data());
        /// 日志生成者类别。平台对象生成的日志信息可以不对用户展示。
        /// 平台对象(1)、应用对象(2)、其他待定
        log.ucSrcType = 2;
        /// 下面3项可由具体项目定义
        /// 警告级别
        /// 提示(1)、告警(2)、错误(3)
        log.ucWarningLevel = level;
        /// 主类型
        /// 分为用户操控(1)和设备工作(2)
        log.ucMainType = 1;
        /// 子类型
        /// 用户操控的子类型分为：0x001--界面操作；0x002--用户管理；
        /// 设备工作的子类型分为：0x001--设备状态；0x002--内部接口；0x003--外部部接口；
        log.ucSubType = 1;
        /// 日志内容
        strcpy(log.szContent, strLog.toUtf8().data());

        pLogMgr->Add(log);

        return 1;
    }

    return -1;
}
#endif

#ifdef PLATFORM_NONE
int Log::writeLog(ushort objectID, Log_Level level, QString strMsg)
{
    return -1;
}

/**
 * @brief writeLog  写日志
 * @param level     日志级别 1：提示 2：告警 3：错误
 * @param msgHead   日志头（记录文件、函数、行）
 * @param strMsg    自定义日志体
 * @return
 */
int Log::writeLog(Log_Level level, QString msgHead, QString strMsg)
{
    QString strLog;
    switch(level)
    {
        case LOG_LEVEL_PROMPT:
        strLog = msgHead + QString("提示：") + strMsg;
        break;
        case LOG_LEVEL_WARNING:
        strLog = msgHead + QString("警告：") + strMsg;
        break;
        case LOG_LEVEL_ERROR:
        strLog = msgHead + QString("错误：") + strMsg;
        break;
    }
    qDebug() << strLog;
    return 1;
}
#endif


#ifdef PLATFORM_BRIT
#endif

