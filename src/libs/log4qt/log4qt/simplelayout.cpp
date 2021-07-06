/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/simplelayout.h"

#include <QtCore/QDebug>
#include "log4qt/loggingevent.h"



namespace  Log4Qt
{
	
	
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * Class implementation: SimpleLayout
	 **************************************************************************/
	
	
	QString SimpleLayout::format(const LoggingEvent &rEvent)
	{
	    return rEvent.level().toString() + QLatin1String(" - ") + rEvent.message() + Layout::endOfLine();
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug SimpleLayout::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "SimpleLayout(" 
	        << "name:" << name() << " "
	        << "referencecount:" << referenceCount()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
} // namespace Log4Qt
