#include "ttccombination.h"
#include "guiservice.h"
#include "log.h"
#include "Bundle.h"
#include "communication_define.h"
TTCCombination::TTCCombination(BundleContext context,const ChannelAttributes &attrs, CommunicationService *communicationService, QObject *parent)
    :CommunicationServiceBase(attrs,communicationService), m_context(context)
{

}
void TTCCombination::dataOpr(const MessageSharePointer data)
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
        gui_service->SendMessge(array,CHANNEL_ID_TTCCombination);
    }
    else {
        qDebug() << "error";
    }
}
