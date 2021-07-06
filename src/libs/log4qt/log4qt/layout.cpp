/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/layout.h"

#include <QtCore/QDebug>
#include "log4qt/loggingevent.h"
#include "log4qt/logmanager.h"



namespace Log4Qt
{
	
	
	/***************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * Class implementation: Layout
	 **************************************************************************/
	
	
	QString Layout::contentType() const
	{
	    return QString::fromLatin1("text/plain");
	}
	    
	
	void Layout::activateOptions()
	{
	}
	
	
	QString Layout::endOfLine()
	{
		// There seams to be no function in Qt for this
		
#ifdef Q_OS_WIN32
		return QLatin1String("\r\n");
#endif // Q_OS_WIN32
//#ifdef Q_OS_MAC
//		return QLatin1String("\r");
//#endif // Q_OS_MAC
		return QLatin1String("\n");
	}
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
} // namespace Log4Qt
