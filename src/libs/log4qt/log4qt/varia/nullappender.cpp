/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/nullappender.h"

#include <QtCore/QDebug>
#include "log4qt/layout.h"
#include "log4qt/loggingevent.h"



namespace Log4Qt
{
	
	
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * Class implementation: NullAppender
	 **************************************************************************/
	
	
	NullAppender::NullAppender(QObject *pParent) :
	    AppenderSkeleton(false, pParent)
	{
	}
	
	
	NullAppender::~NullAppender()
	{
	    close();
	}
	
	
	void NullAppender::append(const LoggingEvent &rEvent)
	{
	    Q_UNUSED(rEvent);
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug NullAppender::debug(QDebug &rDebug) const
	{
	    QString layout_name;
	    if (layout())
	        layout_name = layout()->name();
	    
	    rDebug.nospace() << "NullAppender(" 
	        << "name:" << name() << " "
	        << "isactive:" << isActive() << " "
	        << "isclosed:" << isClosed() << " "
	        << "layout:" << layout_name << " "
	        << "threshold:" << threshold().toString() << " "
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
} // namespace Log4Qt
