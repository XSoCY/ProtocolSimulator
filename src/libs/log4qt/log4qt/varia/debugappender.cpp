/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/varia/debugappender.h"

#include <QtCore/QDebug>
#include <stdio.h>
#include "log4qt/layout.h"
#include "log4qt/loggingevent.h"
#if defined(Q_WS_WIN) || defined(Q_OS_WIN32)
  #include <Windows.h>
#endif

namespace Log4Qt
{
	
	
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
	
	
	/**************************************************************************
	 * Class implementation: DebugAppender
	 **************************************************************************/
	
	
	DebugAppender::DebugAppender(Layout *pLayout,
	                             QObject *pParent) :
	    AppenderSkeleton(pParent)
	{
		setLayout(pLayout);
	}
	
	
	bool DebugAppender::requiresLayout() const
	{   
	    return true;
	}
	
	
	void DebugAppender::append(const LoggingEvent &rEvent)
	{
	    // Q_ASSERT_X(, "DebugAppender::append()", "Lock must be held by caller");
	    Q_ASSERT_X(layout(), "DebugAppender::append()", "Layout must not be null");
	    
        QString message(layout()->format(rEvent));
#if defined(Q_OS_WIN32) || defined(Q_WS_WIN)
  #if (QT_VERSION < 0x050000)
        QT_WA({
                  OutputDebugStringW(reinterpret_cast<const WCHAR*>(message.utf16()));
              }, {
                  OutputDebugStringA(message.toLocal8Bit().data());
              });
  #else
        OutputDebugStringW(reinterpret_cast<const WCHAR*>(message.utf16()));
  #endif
#else
        fprintf(stderr, message.toLocal8Bit().data());
        fflush(stderr);
#endif
	}
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/
	
	
#ifndef QT_NO_DEBUG_STREAM
	QDebug DebugAppender::debug(QDebug &rDebug) const
	{
	    QString layout_name;
	    if (layout())
	        layout_name = layout()->name();
	    
	    rDebug.nospace() << "DebugAppender(" 
	        << "name:" << name() << " "
	        << "filter:" << firstFilter() << " "
	        << "isactive:" << isActive() << " "
	        << "isclosed:" << isClosed() << " "
	        << "layout:" << layout_name << " "
	        << "referencecount:" << referenceCount() << " "
	        << "threshold:" << threshold().toString()
	        << ")";
	    return rDebug.space();    
	}
#endif // QT_NO_DEBUG_STREAM
	
	
} // namspace Log4Qt
