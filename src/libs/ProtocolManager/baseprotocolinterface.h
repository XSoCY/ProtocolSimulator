#ifndef BASEPROTOCOLINTERFACE_H
#define BASEPROTOCOLINTERFACE_H
#include "CommonDefine/commonprotocolstruct.h"
#include <QVector>
/***************************************************************************
*    class        : baseprotocolinterface.h
*    description  : 数据域的解析接口  ： 根据不同数据域类型，但基本协议头是一定的。把针对数据域的变化，封装到继承类中。
*    Author       : FengYu
*    Time         : 2021-06-24  09:51
*    others       :
**************************************************************************/
class BaseProtocolInterface
{
public:
    BaseProtocolInterface(){}
    virtual ~BaseProtocolInterface(){}
public:
    /*************************************************************************
    *    class        : BaseProtocolInterface.h
    *    Function     :
    *    Parameters   :  dataStream  数据域 ： 去掉基本帧头，以及校验。
    *                    baseHead    基本帧头 ： 可能需要帧头里面的参数，此处传递进来，后期若不需要可以删除
    *                    vectorParameterData 存放所有解析出来的参数
    *    ReturnValue  ： 解析成功 true  否则 false
    *    Author       : FengYu
    *    Time         : 2021-06-24  10:53
    *    others       :
    **************************************************************************/
    virtual bool getDisplayDataFromByteArry(QDataStream& dataStream,
                                            BaseFram_t&  baseHead,
                                            QVector<CommunicationParameterData_t>& vectorParameterData
                                            ) = 0;

};
#endif // BASEPROTOCOLINTERFACE_H
