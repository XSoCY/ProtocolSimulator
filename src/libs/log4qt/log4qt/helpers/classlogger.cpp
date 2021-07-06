/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/helpers/classlogger.h"

#include <QtCore/QDebug>
#include "log4qt/logmanager.h"


namespace Log4Qt
{


	/**************************************************************************
	 * Declarations
	 **************************************************************************/



	/**************************************************************************
	 * C helper functions
	 **************************************************************************/



	/**************************************************************************
	 * Class implementation: ClassLogger
	 **************************************************************************/


	ClassLogger::ClassLogger() :
	    mpLogger(0)
	{
	}


	Logger *ClassLogger::logger(const QObject *pObject)
	{
		Q_ASSERT_X(pObject, "ClassLogger::logger()", "pObject must not be null");
#if QT_VERSION < QT_VERSION_CHECK(4, 4, 0)
	    if (!mpLogger)
	        q_atomic_test_and_set_ptr(&mpLogger,
									  0,
									  LogManager::logger(QLatin1String(pObject->metaObject()->className())));
	    return const_cast<Logger *>(mpLogger);
#elif QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        if (!static_cast<Logger *>(mpLogger))
             mpLogger.testAndSetOrdered(0,
                                        LogManager::logger(QLatin1String(pObject->metaObject()->className())));
        return const_cast<Logger *>(static_cast<Logger *>(mpLogger));
#else
        if (!static_cast<Logger *>(mpLogger.loadAcquire()))
			 mpLogger.testAndSetOrdered(0,
										LogManager::logger(QLatin1String(pObject->metaObject()->className())));
        return const_cast<Logger *>(static_cast<Logger *>(mpLogger.loadAcquire()));
#endif
	}



	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/



} // namespace Log4Qt
