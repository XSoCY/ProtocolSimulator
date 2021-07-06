#ifndef AVTIVATOR_H
#define AVTIVATOR_H
#include "BundleActivator.h"
#include "BundleContext.h"
#include "communicationservice.h"
#include "ServiceProperties.h"
#include "guiservice.h"
#include <memory>
#include <set>
#include "communication_define.h"
#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "sqltableform.h"
using namespace cppmicroservices;

namespace
{

/**
 * This class implements a bundle activator that uses the bundle
 * context to register an English language dictionary service
 * with the C++ Micro Services registry during static initialization
 * of the bundle. The dictionary service interface is
 * defined in a separate file and is implemented by a nested class.
 */
class US_ABI_LOCAL CommunicationActivator : public QObject, public BundleActivator
{
    Q_OBJECT
private:

public:
    /**
     * Implements BundleActivator::Start(). Registers an
     * instance of a dictionary service using the bundle context;
     * attaches properties to the service that can be queried
     * when performing a service look-up.
     * @param context the context for the bundle.
     */

    void Start(BundleContext context)
    {
        QString path = QDir::currentPath();
        qDebug() << "path:" << path;

        path += "//configs//channels.xml";


        m_ComService = std::make_shared<CommunicationService>(path, context);

        ServiceProperties props;
        props["Type"] = std::string("CommunicationService");
        context.RegisterService<ICommunicationServiceInterface>(m_ComService, props);


        m_guiService = std::make_shared<GuiService>(context);

        ServiceProperties props2;
        props2["Type"] = std::string("GUI");
        context.RegisterService<IGuiServiceInterface>(m_guiService, props2);

        //线程初始化
    }

    /**
     * Implements BundleActivator::Stop(). Does nothing since
     * the C++ Micro Services library will automatically unregister any registered services.
     * @param context the context for the bundle.
     */
    void Stop(BundleContext /*context*/)
    {

    }

private:
    std::shared_ptr<GuiService> m_guiService;
    std::shared_ptr<CommunicationService> m_ComService;

};
}  // namespace

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(CommunicationActivator)
#endif // AVTIVATOR_H
