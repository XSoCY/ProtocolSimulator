#ifndef TTCFRONTCOMPUTER_H
#define TTCFRONTCOMPUTER_H
#include <QByteArray>
#include "tcpchannel.h"
#include "BundleContext.h"
#include "communicationservicebase.h"
using namespace cppmicroservices;
//测发控前端计算机
class TTCFrontComputer: public CommunicationServiceBase
{
public:
    TTCFrontComputer(BundleContext context,const ChannelAttributes &attrs, CommunicationService *communicationService, QObject *parent = nullptr);
protected:
    /**
     * @brief DataOpr 处理此通道收到的数据
     * @param data 收到客户端数据
     * @return 无
     */
    void dataOpr(const MessageSharePointer data);
    BundleContext       m_context;
};

#endif // TTCFRONTCOMPUTER_H
