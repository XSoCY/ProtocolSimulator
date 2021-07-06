/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/levelrangefilter.h"

#include <QtCore/QDebug>
#include "log4qt/loggingevent.h"


namespace Log4Qt
{


/******************************************************************************
 * Declarations
 ******************************************************************************/



/******************************************************************************
 * C helper functions
 ******************************************************************************/



/******************************************************************************
 * Class implementation: Filter
 ******************************************************************************/


LevelRangeFilter::LevelRangeFilter(QObject *pParent) :
    Filter(pParent),
    mAcceptOnMatch(true),
    mLevelMin(Level::NULL_INT),
    mLevelMax(Level::OFF_INT)
{}


Filter::Decision LevelRangeFilter::decide(const LoggingEvent &rEvent) const
{
    if (rEvent.level() < mLevelMin) 
        return Filter::DENY;

    if (rEvent.level() > mLevelMax) 
        return Filter::DENY;
    
    if (mAcceptOnMatch)
	    return Filter::ACCEPT;
    else
        return Filter::NEUTRAL;
}


#ifndef QT_NO_DEBUG_STREAM
QDebug LevelRangeFilter::debug(QDebug &rDebug) const
{
    rDebug.nospace() << "LevelRangeFilter("
        << "acceptonmatch:" << mAcceptOnMatch << " "
        << "levelmin:" << mLevelMin.toString() << " "
        << "levelmax:" << mLevelMax.toString() << " "
        << "next:" << next()
        << "referencecount:" << referenceCount() << " "
        << ")";
    return rDebug.space();
}
#endif // QT_NO_DEBUG_STREAM



/******************************************************************************
 * Implementation: Operators, Helper
 ******************************************************************************/



} // namespace Log4Qt
