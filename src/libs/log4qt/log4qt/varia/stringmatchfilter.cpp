/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/stringmatchfilter.h"

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
	
	
	StringMatchFilter::StringMatchFilter(QObject *pParent) :
	    Filter(pParent),
	    mAcceptOnMatch(true),
	    mStringToMatch()
	{}
	
	
	Filter::Decision StringMatchFilter::decide(const LoggingEvent &rEvent) const
	{
	    if (rEvent.message().isEmpty() ||  
	        mStringToMatch.isEmpty() ||
	        rEvent.message().indexOf(mStringToMatch) < 0)
	        return Filter::NEUTRAL;
	    
	    if (mAcceptOnMatch)
		    return Filter::ACCEPT;
	    else
	        return Filter::DENY;
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug StringMatchFilter::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "StringMatchFilter("
	        << "acceptonmatch:" << mAcceptOnMatch << " "
	        << "referencecount:" << referenceCount() << " "
	        << "stringtomatch:" << mStringToMatch << " "
	        << "next:" << next()
	        << ")";
	    return rDebug.space();
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
	
} // namespace Log4Qt
