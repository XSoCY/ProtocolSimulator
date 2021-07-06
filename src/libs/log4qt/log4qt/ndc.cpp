/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/ndc.h"

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
	
	
    LOG4QT_DECLARE_STATIC_LOGGER(logger, Log4Qt:NDC)    
 
	
	
	/**************************************************************************
	 * Class implementation: NDC
	 **************************************************************************/
	
	
	void NDC::clear()
	{
	    if (!instance()->mStack.hasLocalData())
	        return;
	    
	    instance()->mStack.localData()->clear();
	}    
	
	
	int NDC::depth()
	{
	    if (!instance()->mStack.hasLocalData())
	        return 0;
	        
	    return instance()->mStack.localData()->count();
	}
    
	
    LOG4QT_IMPLEMENT_INSTANCE(NDC)
	
	
	QString NDC::pop()
	{
	    if (!instance()->mStack.hasLocalData() || instance()->mStack.localData()->isEmpty())
	    {
	        logger()->warn("Requesting pop from empty NDC stack");        
	        return QString();
	    }
	    
	    return instance()->mStack.localData()->pop();
	}
	
	
	void NDC::push(const QString &rMessage)
	{
	    if (!instance()->mStack.hasLocalData())
	        instance()->mStack.setLocalData(new QStack<QString>);
	    
	    instance()->mStack.localData()->push(rMessage);
	}
	
	
	void NDC::setMaxDepth(int maxDepth)
	{
	    if (!instance()->mStack.hasLocalData() || 
	        instance()->mStack.localData()->size() <= maxDepth)
	        return;
	
	    instance()->mStack.localData()->resize(maxDepth);
	}
	
	
	QString NDC::peek()
	{
	    if (!instance()->mStack.hasLocalData() || 
	        instance()->mStack.localData()->isEmpty())
	        return QString();
	    
	    return instance()->mStack.localData()->top();
	}
    
    
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug operator<<(QDebug debug,
	                  const NDC &rNDC)
	{
		Q_UNUSED(rNDC); // To avoid warning C4100 on VS 2008
	    debug.nospace() << "NDC(" 
	        << "thread:" << QThread::currentThread()->objectName() << " "
	        << "peek:" << rNDC.peek() << " "
	        << "depth:" << rNDC.depth()
	        << ")";
	    return debug.space();
	}
#endif // QT_NO_DEBUG_STREAM
	
	
} // namespace Log4Qt
