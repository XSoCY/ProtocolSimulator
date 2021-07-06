/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/ttcclayout.h"

#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include "log4qt/helpers/datetime.h"
#include "log4qt/helpers/patternformatter.h"
#include "log4qt/logger.h"
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
	 * Class implementation: TTCCLayout
	 **************************************************************************/
	
	
	TTCCLayout::TTCCLayout(QObject *pParent) :
	    Layout(pParent),
		mCategoryPrefixing(true),
		mContextPrinting(true),
	    mDateFormat(),
	    mThreadPrinting(true),
	    mpPatternFormatter(0)
	{
        setDateFormat(TIME_RELATIVE);
	}
	
	
	TTCCLayout::TTCCLayout(const QString &rDateFormat, 
	                       QObject *pParent) :
	    Layout(pParent),
		mCategoryPrefixing(true),
		mContextPrinting(true),
	    mDateFormat(rDateFormat),
	    mThreadPrinting(true),
	    mpPatternFormatter(0)
	{
	}
	
	
	TTCCLayout::TTCCLayout(DateFormat dateFormat, 
	                       QObject *pParent) :
	    Layout(pParent),
		mCategoryPrefixing(true),
		mContextPrinting(true),
	    mDateFormat(),
	    mThreadPrinting(true),
	    mpPatternFormatter(0)
	{
	    setDateFormat(dateFormat);
	}
	
	
	TTCCLayout::~TTCCLayout()
	{
		delete mpPatternFormatter;
	}
	
	
	void TTCCLayout::setDateFormat(DateFormat dateFormat)
	{
	    switch (dateFormat)
	    {
	        case NONE:
	        	setDateFormat(QLatin1String("NONE"));
	            break;
	        case ISO8601:
	        	setDateFormat(QLatin1String("ISO8601"));
	            break;
            case TIME_ABSOLUTE:
                setDateFormat(QLatin1String("TIME_ABSOLUTE"));
	            break;
	        case DATE:
	        	setDateFormat(QLatin1String("DATE"));
	            break;
            case TIME_RELATIVE:
                setDateFormat(QLatin1String("TIME_RELATIVE"));
	            break;
	        default:
	            Q_ASSERT_X(false, "TTCCLayout::setDateFormat", "Unkown DateFormat");
	            setDateFormat(QString());
	    }
	}
	
	
	QString TTCCLayout::format(const LoggingEvent &rEvent)
	{
		Q_ASSERT_X(mpPatternFormatter, "TTCCLayout::format()", "mpPatternConverter must not be null");
		
		return mpPatternFormatter->format(rEvent);
	}
	
	
	void TTCCLayout::updatePatternFormatter()
	{
		QString pattern;
		
		pattern += QLatin1String("%d{") +  mDateFormat + QLatin1String("}");
		if (mThreadPrinting)
			pattern += QLatin1String(" [%t]");
		pattern += QLatin1String(" %-5p");
		if (mCategoryPrefixing)
			pattern += QLatin1String(" %c");
		if (mContextPrinting)
			pattern += QLatin1String(" %x");
		pattern += QLatin1String(" - %m%n");
	
		delete mpPatternFormatter;
		mpPatternFormatter = new PatternFormatter(pattern);
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug TTCCLayout::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "TTCCLayout(" 
	        << "name:" << name() << " "
	        << "categoryprefixing:" << categoryPrefixing() << " "
	        << "contextprinting:" << contextPrinting() << " "
	        << "dateformat:" << dateFormat() << " "
	        << "referencecount:" << referenceCount() << " "
	        << "threadprinting:" << threadPrinting()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	    
} // namespace Log4Qt
