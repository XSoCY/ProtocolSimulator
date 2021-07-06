/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/listappender.h"

#include <QtCore/QDebug>



namespace Log4Qt
{
	    
	
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * Class implementation: ListAppender
	 **************************************************************************/
	
	
	ListAppender::ListAppender(QObject *pParent) :
	    AppenderSkeleton(pParent),
	    mConfiguratorList(false),
	    mList(),
	    mMaxCount(0)
	{
	}
	
	
	ListAppender::~ListAppender()
	{
	}
	
	
	QList<LoggingEvent> ListAppender::list() const
	{
	    QMutexLocker locker(&mObjectGuard);
	
	    return mList;
	}
	
	
	void ListAppender::setMaxCount(int n)
	{
	    QMutexLocker locker(&mObjectGuard);
	    
	    if (n < 0)
	    {
	        logger()->warn("Attempt to set maximum count for appender '%1' to %2. Using zero instead", name(), n);
	        n = 0;
	    }
	    mMaxCount = n;
	    ensureMaxCount();
	}
	
	
	QList<LoggingEvent> ListAppender::clearList()
	{
	    QMutexLocker locker(&mObjectGuard);
	    
	    QList<LoggingEvent> result = mList;
	    mList.clear();
	    return result;
	}
	
	
	// bool ListAppender::requiresLayout() const;
	
	
	void ListAppender::append(const LoggingEvent &rEvent)
	{
	    // Q_ASSERT_X(, "ListAppender::append()", "Lock must be held by caller")
	    
	    if ((mMaxCount <= 0) || (mList.size() < mMaxCount))
	        mList << rEvent;
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug ListAppender::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "ListAppender(" 
	        << "name:" << name() << " "
	        << "count:" <<  list().count() << " "
	        << "filter:" << firstFilter() << " "
	        << "isactive:" << isActive() << " "
	        << "isclosed:" << isClosed() << " "
	        << "maxcount:" <<  maxCount() << " "
	        << "referencecount:" << referenceCount() << " "
	        << "threshold:" << threshold().toString()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	void ListAppender::ensureMaxCount()
	{
	    // Q_ASSERT_X(, "ListAppender::ensureMaxCount()", "Lock must be held by caller")
	
	    if (mMaxCount <= 0)
	        return;
	    
	    while (mList.size() > mMaxCount)
	        mList.removeFirst();
	}
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	    
} // namespace Log4Qt
