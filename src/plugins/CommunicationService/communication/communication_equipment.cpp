#include "communication_equipment.h"
#include "guiservice.h"
#include "log.h"
#include "Bundle.h"
#include "multsingletableselprotocol.h"
#include "communication_define.h"
Communication_Equipment::Communication_Equipment(BundleContext context,const ChannelAttributes &attrs, CommunicationService *communicationService, QObject *parent)
    :CommunicationServiceBase(attrs,communicationService), m_context(context)
{

}

void Communication_Equipment::dataOpr(const MessageSharePointer data)
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
        gui_service->SendMessge(array,CHANNEL_ID_Equipment);
    }
    else {
        qDebug() << "error";
    }
    //
}
