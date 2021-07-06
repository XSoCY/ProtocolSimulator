#ifndef COMMUNICATION_EQUIPMENT_H
#define COMMUNICATION_EQUIPMENT_H

#include <QByteArray>
#include "tcpchannel.h"
#include "BundleContext.h"
#include "communicationservicebase.h"
using namespace cppmicroservices;
/***************************************************************************
*    class        : communication_equipment.h
*    description  :  参数设备
*    Author       : FengYu
*    Time         : 2021-06-29  15:34
*    others       :
**************************************************************************/
class Communication_Equipment : public CommunicationServiceBase
{
    Q_OBJECT
public:
    Communication_Equipment(BundleContext context,const ChannelAttributes &attrs, CommunicationService *communicationService, QObject *parent = nullptr);

protected:
    /**
     * @brief DataOpr 处理此通道收到的数据
     * @param data 收到客户端数据
     * @return 无
     */
    void dataOpr(const MessageSharePointer data);

    BundleContext       m_context;
};

#endif // COMMUNICATION_EQUIPMENT_H
