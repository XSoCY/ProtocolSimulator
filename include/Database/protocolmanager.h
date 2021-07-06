#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H

#include "protocolmanager_global.h"
#include "baseprotocolinterface.h"
/***************************************************************************
*    class        : protocolmanager.h
*    description  : 管理所有协议对象
*    Author       : FengYu
*    Time         : 2021-06-24  11:05
*    others       :
**************************************************************************/
class PROTOCOLMANAGERSHARED_EXPORT ProtocolManager
{

public:
    ProtocolManager();
    ~ProtocolManager();
    BaseProtocolInterface * getDataSegTypeFramProtocol(const ProtocolType &protocoltype);

private:
    BaseProtocolInterface * m_multsingletablesel;//多单表结构
};

#endif // PROTOCOLMANAGER_H
