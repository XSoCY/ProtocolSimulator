/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/helpers/initialisationhelper.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QMutex>
#include <QtCore/QProcess>
#include <QtCore/QSettings>
#ifndef QT_NO_DATASTREAM
#include <QtCore/QDataStream>
#endif
#include "log4qt/helpers/datetime.h"
#include "log4qt/helpers/logerror.h"
#include "log4qt/loggingevent.h"



namespace Log4Qt
{
	
	    
	/**************************************************************************
	 *Declarations
	 **************************************************************************/
	
	
	    
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/
	
        
    
	/**************************************************************************
	 * Class implementation: InitialisationHelper
	 **************************************************************************/
	
	    
	InitialisationHelper::InitialisationHelper() :
	    mStartTime(DateTime::currentDateTime().toMilliSeconds()),
	    mEnvironmentSettings()
	{
		doRegisterTypes();
		doInitialiseEnvironmentSettings();
	}
	    
	    
	InitialisationHelper::~InitialisationHelper()
	{
	    Q_ASSERT_X(false, "InitialisationHelper::~InitialisationHelper()", "Unexpected destruction of singleton object");
	}
	
	
    LOG4QT_IMPLEMENT_INSTANCE(InitialisationHelper)

    
	void InitialisationHelper::doInitialiseEnvironmentSettings()
	{
		// Is Process::systemEnvironment() safe to be used before a QCoreApplication
		// object has been created?
		
		QStringList setting_keys;
		setting_keys << QLatin1String("Debug");
		setting_keys << QLatin1String("DefaultInitOverride");
		setting_keys << QLatin1String("Configuration");
		setting_keys << QLatin1String("ConfiguratorClass");
		
		QHash<QString, QString> env_keys;
		QString entry;
		Q_FOREACH(entry, setting_keys)
			env_keys.insert(QString::fromLatin1("log4qt_").append(entry).toUpper(), entry);

		QStringList sys_env = QProcess::systemEnvironment();
		Q_FOREACH(entry, sys_env)
		{
			int i = entry.indexOf(QLatin1Char('='));
			if (i == -1)
				continue;
			QString key = entry.left(i);
			QString value = entry.mid(i + 1).trimmed();
			if (env_keys.contains(key))
			    mEnvironmentSettings.insert(env_keys.value(key), value);
		}
	}
	
	
	void InitialisationHelper::doRegisterTypes()
	{
	    qRegisterMetaType<Log4Qt::LogError>("Log4Qt::LogError");
        qRegisterMetaType<Log4Qt::Level>("Log4Qt::Level");
        qRegisterMetaType<Log4Qt::LoggingEvent>("Log4Qt::LoggingEvent");
	
	#ifndef QT_NO_DATASTREAM
        qRegisterMetaTypeStreamOperators<Log4Qt::LogError>("Log4Qt::LogError");
        qRegisterMetaTypeStreamOperators<Log4Qt::Level>("Log4Qt::Level");
	    qRegisterMetaTypeStreamOperators<LoggingEvent>("Log4Qt::LoggingEvent");
	#endif
	}
	
	
    QString InitialisationHelper::doSetting(const QString &rKey, 
                                            const QString &rDefault) const
    {
        if (mEnvironmentSettings.contains(rKey))
            return mEnvironmentSettings.value(rKey);
        
        if (QCoreApplication::instance())
        {
            QSettings s;
            s.beginGroup(QLatin1String("Log4Qt"));
            return s.value(rKey, rDefault).toString().trimmed();
        }
        else
            return rDefault;
    }
	
    
	bool InitialisationHelper::staticInitialisation()
	{
	    instance();
	    return true;
	}
	
	
	bool InitialisationHelper::msStaticInitialisation = staticInitialisation();
	
	
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/

	
#ifndef QT_NO_DEBUG_STREAM
	QDebug operator<<(QDebug debug, 
	                  const InitialisationHelper &rInitialisationHelper)
	{
		Q_UNUSED(rInitialisationHelper);
		debug.nospace() << "InitialisationHelper("
			<< "starttime:" << InitialisationHelper::startTime()
            << "(" << DateTime::fromMilliSeconds(InitialisationHelper::startTime()) << ")"
	        << "environmentsettings:" << InitialisationHelper::environmentSettings()
	        << ")";
		return debug.space();
	}
#endif // QT_NO_DEBUG_STREAM

	
	
} // namespace Log4Qt
