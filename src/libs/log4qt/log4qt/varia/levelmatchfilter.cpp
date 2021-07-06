/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/levelmatchfilter.h"

#include <QtCore/QDebug>
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
	 * Class implementation: Filter
	 **************************************************************************/
	
	
	LevelMatchFilter::LevelMatchFilter(QObject *pParent) :
	    Filter(pParent),
	    mAcceptOnMatch(true),
	    mLevelToMatch(Level::NULL_INT)
	{}
	
	
	Filter::Decision LevelMatchFilter::decide(const LoggingEvent &rEvent) const
	{
	    if (mLevelToMatch == Level::NULL_INT || 
	        rEvent.level() != mLevelToMatch)
	        return Filter::NEUTRAL;
	    
	    if (mAcceptOnMatch)
		    return Filter::ACCEPT;
	    else
	        return Filter::DENY;
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug LevelMatchFilter::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "LevelMatchFilter("
	        << "acceptonmatch:" << mAcceptOnMatch << " "
	        << "leveltomatch:" << mLevelToMatch.toString() << " "
	        << "next:" << next()
	        << "referencecount:" << referenceCount() << " "
	        << ")";
	    return rDebug.space();
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
	
} // namespace Log4Qt
