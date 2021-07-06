#include "ttcfrontcomputer.h"
#include "guiservice.h"
#include "log.h"
#include "Bundle.h"
#include "communication_define.h"
TTCFrontComputer::TTCFrontComputer(BundleContext context,const ChannelAttributes &attrs, CommunicationService *communicationService, QObject *parent)
    :CommunicationServiceBase(attrs,communicationService), m_context(context)
{

}
void TTCFrontComputer::dataOpr(const MessageSharePointer data)
{
    if( !data || !m_communicationService )
    {
        return;
    }
    auto serviceRef = m_context.GetServiceReference<IGuiServiceInterface>();

    std::shared_ptr<IGuiServiceInterface> gui_service =
        m_context.GetService<IGuiServiceInterface>(serviceRef);
    if (gui_service.get())
    {
        QByteArray array(data->data(),data->size());
        gui_service->SendMessge(array,CHANNEL_ID_TTCFrontCompter);
    }
    else {
        qDebug() << "error";
    }
}
