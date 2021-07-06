/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/mdc.h"

#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include "log4qt/helpers/initialisationhelper.h"
#include "log4qt/logger.h"



namespace Log4Qt
{
	
	
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
 
    
	
	/**************************************************************************
	 * Class implementation: MDC
	 **************************************************************************/
	
	
	QString MDC::get(const QString &rKey)
	{
	    if (!instance()->mHash.hasLocalData())
	        return QString();
	
	    return instance()->mHash.localData()->value(rKey);
	}
	
	
	QHash<QString, QString> MDC::context()
	{
	    if (!instance()->mHash.hasLocalData())
	        return QHash<QString, QString>();
	    
	    return *instance()->mHash.localData();
	}
	
	
    LOG4QT_IMPLEMENT_INSTANCE(MDC)
    

	QHash<QString, QString> *MDC::localData()
	{
	    if (!instance()->mHash.hasLocalData())
	        instance()->mHash.setLocalData(new QHash<QString, QString>);
	    return instance()->mHash.localData();
	}   

	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug operator<<(QDebug debug, const MDC &rMDC)
	{
		Q_UNUSED(rMDC); // To avoid warning C4100 on VS 2008
	    debug.nospace() << "MDC(" 
	        << "thread:" << QThread::currentThread()->objectName() << " "
	        << "context:" << rMDC.context()
	        << ")";
	    return debug.space();
	}
#endif // QT_NO_DEBUG_STREAM
	
	
} // namespace Log4Qt
