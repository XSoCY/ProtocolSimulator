/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/helpers/configuratorhelper.h"

#include <QtCore/QDebug>
#include <QtCore/QFileSystemWatcher>
#include "log4qt/helpers/initialisationhelper.h"



namespace Log4Qt
{
	
	    
	/**************************************************************************
	 * Declarations
	 **************************************************************************/
	
	
	    
	/**************************************************************************
	 * C helper functions
	 **************************************************************************/

    
	
	/**************************************************************************
	 * Class implementation: ConfiguratorHelper
	 **************************************************************************/
	
	    
	ConfiguratorHelper::ConfiguratorHelper() :
		mObjectGuard(),
	    mConfigurationFile(),
	    mpConfigureFunc(0),
	    mpConfigurationFileWatch(0),
		mConfigureError()
	{
	}
	    
	    
	ConfiguratorHelper::~ConfiguratorHelper()
	{
	    delete mpConfigurationFileWatch;
	}

    
    LOG4QT_IMPLEMENT_INSTANCE(ConfiguratorHelper)

    
    void ConfiguratorHelper::doConfigurationFileChanged(const QString &rFileName)
	{	
	    QMutexLocker locker(&mObjectGuard);

	    if (!mpConfigureFunc)
			return;
	    mpConfigureFunc(rFileName);
		// Shall we hold the lock while emitting the signal?
		emit configurationFileChanged(rFileName, mConfigureError.count() > 0);
	}
	

	
    void ConfiguratorHelper::doSetConfigurationFile(const QString &rFileName,
                                                  ConfigureFunc pConfigureFunc)
    {
	    QMutexLocker locker(&mObjectGuard);

	    mConfigurationFile.clear();
	    mpConfigureFunc = 0;
	    delete mpConfigurationFileWatch;
		if (rFileName.isEmpty())
	    	return;

		mConfigurationFile = rFileName;
    	mpConfigureFunc = pConfigureFunc;
    	mpConfigurationFileWatch = new QFileSystemWatcher();
    	mpConfigurationFileWatch->addPath(rFileName);
    	connect(mpConfigurationFileWatch, 
    			SIGNAL(fileChanged(const QString &)), 
    			SLOT(configurationFileChanged(const QString &)));
    }
    
    
	
	/**************************************************************************
	 * Implementation: Operators, Helper
	 **************************************************************************/

	
#ifndef QT_NO_DEBUG_STREAM
	QDebug operator<<(QDebug debug, 
	                  const ConfiguratorHelper &rConfiguratorHelper)
	{
		debug.nospace() << "ConfiguratorHelper("
			<< "configurationfile:" << ConfiguratorHelper::configurationFile()
			<< "configurefunc:" << rConfiguratorHelper.mpConfigureFunc
			<< "filesystemwatcher:" << rConfiguratorHelper.mpConfigurationFileWatch
	        << ")";
		return debug.space();
	}
#endif // QT_NO_DEBUG_STREAM

	
	
} // namespace Log4Qt

