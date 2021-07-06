/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/patternlayout.h"

#include <QtCore/QDebug>
#include "log4qt/helpers/patternformatter.h"
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
	 * Class implementation: PatternLayout
	 **************************************************************************/
	
	
	PatternLayout::PatternLayout(QObject *pParent) :
	    Layout(pParent),
	    mPattern(),
	    mpPatternFormatter(0)
	{
		setConversionPattern(DEFAULT_CONVERSION_PATTERN);
	}
	
	
	PatternLayout::PatternLayout(const QString &rPattern,
	                             QObject *pParent) :
	    Layout(pParent),
	    mPattern(),
	    mpPatternFormatter(0)
	{
		setConversionPattern(rPattern);
	}
	
	
	PatternLayout::PatternLayout(ConversionPattern conversionPattern,
	                             QObject *pParent) :
	    Layout(pParent),
	    mPattern(),
	    mpPatternFormatter(0)
	{
		setConversionPattern(conversionPattern);
	}
	
	
	PatternLayout::~PatternLayout()
	{
		delete mpPatternFormatter;
	}
	
	
	void PatternLayout::setConversionPattern(ConversionPattern conversionPattern)
	{
		switch (conversionPattern)
		{
		    case DEFAULT_CONVERSION_PATTERN:
		    	setConversionPattern(QLatin1String("%m%n"));
		        break;
		    case TTCC_CONVERSION_PATTERN:
		    	setConversionPattern(QLatin1String("%r [%t] %p %c %x - %m%n"));
		        break;
		    default:
		        Q_ASSERT_X(false, "PatternLayout::setConversionFormat", "Unkown ConversionFormat");
		        setConversionPattern(QString());
		}
	}
	
	
	QString PatternLayout::format(const LoggingEvent &rEvent)
	{
		Q_ASSERT_X(mpPatternFormatter, "PatternLayout::format()", "mpPatternConverter must not be null");
		
		return mpPatternFormatter->format(rEvent);
	}
	
	
	void PatternLayout::updatePatternFormatter()
	{
		delete mpPatternFormatter;
		mpPatternFormatter = new PatternFormatter(mPattern);
	}
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug PatternLayout::debug(QDebug &rDebug) const
	{
	    rDebug.nospace() << "PatternLayout(" 
	    	<< "name:" << name() << " "
	    	<< "pattern:" << conversionPattern() << " "
	    	<< "referencecount:" << referenceCount()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
} // namespace Log4Qt
