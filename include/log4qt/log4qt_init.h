#ifndef QTEZ4_INIT_LOG_H
#define QTEZ4_INIT_LOG_H

#include <QDebug>
#include <QTextCodec>
#include <QDateTime>
#include <QDir>

using namespace Log4Qt;

void initLogger(const QString &logType)
{
    QDir logdir(QCoreApplication::applicationDirPath() + "/logs/");
    if (!logdir.exists())
        logdir.mkpath(logdir.absolutePath());

    QString logType_ = logType.toLower();
    AppenderSkeleton *appender = NULL;
//    do
//    {
        if("db" == logType_)
        {
            DBAppender *dbAppender = new DBAppender();
            dbAppender->setName("QPCF_DBFileAppender");
            dbAppender->setFile(QFileInfo(logdir, QDateTime::currentDateTime()
                                          .toString("yyyyMMdd_hhmmss")+".db")
                                .filePath());
            dbAppender->activateOptions();
            appender = dbAppender;
//            break;
        }

        else /*if("log" == logType_ || "xml" == logType_ || "json" == logType_)*/
        {
            FileAppender *fileAppender = new FileAppender;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");

            fileAppender->setName("QPCF_PlainFileAppender");
            fileAppender->setEncoding(codec);

            Layout *layout = NULL;
            QString fileSurfix;
            if("log" == logType_)
            {
                layout = new TTCCLayout(TTCCLayout::ISO8601);
                fileSurfix = ".log";
            }
            else if("xml" == logType_)
            {
                layout = new XMLLayout();
                fileSurfix = ".xml";
            }
            else if("json" == logType_)
            {
                layout = new JSONLayout();
                fileSurfix = ".json";
            }
            else
            {
                layout = new TTCCLayout(TTCCLayout::ISO8601);
                fileSurfix = ".log";
            }
            QFileInfo fileinfo(logdir, QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + fileSurfix);
            fileAppender->setFile(fileinfo.filePath());
            fileAppender->setAppendFile(true);
            fileAppender->setLayout(layout);
            fileAppender->activateOptions();
            appender = fileAppender;
//            break;
        }
//    }while(0);

    if(NULL != appender)
    {
        LogManager::setHandleQtMessages(true);

        Logger *logger = Logger::rootLogger();
        logger->removeAllAppenders();
        logger->addAppender(appender);
    }
    else
    {
        qWarning() << "invalid log type:" << logType;
    }
}
#endif
