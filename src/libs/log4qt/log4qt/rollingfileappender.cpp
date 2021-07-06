/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/rollingfileappender.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextCodec>
#include "log4qt/helpers/optionconverter.h"
#include "log4qt/layout.h"
#include "log4qt/loggingevent.h"



namespace Log4Qt
{
	    
	
	/************************************************************************
	Declarations
	*************************************************************************/
	
	
	
	/************************************************************************
	C helper functions
	*************************************************************************/
	
	
	
	/************************************************************************
	Class implementation: RollingFileAppender
	*************************************************************************/
	
	
	RollingFileAppender::RollingFileAppender(QObject *pParent) :
	    FileAppender(pParent),
	    mMaxBackupIndex(1),
	    mMaximumFileSize(10*1024*1024)
	{
	}
	
	
	RollingFileAppender::RollingFileAppender(Layout *pLayout,
	                                         const QString &rFileName,
	                                         QObject *pParent) :
	    FileAppender(pLayout, rFileName, pParent),
	    mMaxBackupIndex(1),
	    mMaximumFileSize(10*1024*1024)
	{
	}
	
	
	RollingFileAppender::RollingFileAppender(Layout *pLayout,
	                                         const QString &rFileName,
	                                         bool append,
	                                         QObject *pParent) :
	    FileAppender(pLayout, rFileName, append, pParent),
	    mMaxBackupIndex(1),
	    mMaximumFileSize(10*1024*1024)
	{
	}
	
	
	RollingFileAppender::~RollingFileAppender()
	{
	    close();
	}
	
	
    void RollingFileAppender::setMaxFileSize(const QString &rMaxFileSize)
    {
        bool ok;
        qint64 max_file_size = OptionConverter::toFileSize(rMaxFileSize, &ok);
        if (ok)
            setMaximumFileSize(max_file_size);
    }

	
	void RollingFileAppender::append(const LoggingEvent &rEvent)
	{
	    // Q_ASSERT_X(, "RollingFileAppender::append()", "Lock must be held by caller")
	
	    FileAppender::append(rEvent);
	    if (writer()->device()->size() > this->mMaximumFileSize)
	        rollOver();
	}
	
	
	void RollingFileAppender::rollOver()
	{
	    // Q_ASSERT_X(, "RollingFileAppender::rollOver()", "Lock must be held by caller")
	    
	    logger()->debug("Rolling over with maxBackupIndex = %1", mMaxBackupIndex);
	
	    closeFile();
	    
	    QFile f;
	    f.setFileName(file() + QLatin1Char('.') + QString::number(mMaxBackupIndex));
	    if (f.exists() && !removeFile(f))
	    	return;
	    
	    QString target_file_name;
	    int i;
	    for (i = mMaxBackupIndex - 1; i >=1; i--)
	    {
	        f.setFileName(file() + QLatin1Char('.') + QString::number(i));
	        if (f.exists())
	        {
	            target_file_name = file() + QLatin1Char('.') + QString::number(i + 1);
	            if (!renameFile(f, target_file_name))
	                return;
	        }
	    }
	
	    f.setFileName(file());
	    target_file_name = file() + QLatin1String(".1");
	    if (!renameFile(f, target_file_name))
	        return;
	    
	    openFile();
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug RollingFileAppender::debug(QDebug &rDebug) const
	{
	    QString layout_name;
	    if (layout())
	        layout_name = layout()->name();
	    QString codec_name;
	    if (encoding())
	        codec_name = QLatin1String(encoding()->name());
	    
	    rDebug.nospace() << "RollingFileAppender(" 
	        << "name:" << name() << " "
	        << "appendfile:" << appendFile() << " "
	        << "bufferedio:" << bufferedIo() << " "
	        << "encoding:" << codec_name << " "
	        << "file:" << file() << " "
	        << "filter:" << firstFilter() << " "
	        << "immediateflush:" << immediateFlush() << " "
	        << "isactive:" << isActive() << " "
	        << "isclosed:" << isClosed() << " "
	        << "layout:" << layout_name << " "
	        << "maxbackupindex:" << maxBackupIndex() << " "
	        << "maximumfilesize:" << maximumFileSize() << " "
	        << "referencecount:" << referenceCount() << " "
	        << "threshold:" << threshold().toString() << " "
	        << "writer:" << writer()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
} // namespace Log4Qt
