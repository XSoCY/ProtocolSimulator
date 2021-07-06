#ifndef MULTSINGLETABLESELPROTOCOL_H
#define MULTSINGLETABLESELPROTOCOL_H
#include "protocolmanager_global.h"
#include "baseprotocolinterface.h"
/***************************************************************************
*    class        : multsingletableselprotocol.h
*    description  : 多表挑点数据的解析类
*    Author       : FengYu
*    Time         : 2021-06-24  10:44
*    others       :
**************************************************************************/

/*
 * 多表挑点协议头
 */
typedef struct MultSigleSelectHeadFram
{
    quint8 paraType;         //参数类型；DataValueType
    quint32 subSegmentTime;  ///子段时间
    quint16 subLength;       ///子段长
    quint16 tableNumber;     ///表号
    friend QDataStream &operator<<(QDataStream &out, const MultSigleSelectHeadFram &dpxp_section_header)
    {
        out<<dpxp_section_header.paraType<<dpxp_section_header.subSegmentTime
          <<dpxp_section_header.subLength<<dpxp_section_header.tableNumber;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, MultSigleSelectHeadFram &dpxp_section_header)
    {
        in>>dpxp_section_header.paraType;
        in>>dpxp_section_header.subSegmentTime;
        in>>dpxp_section_header.subLength;
        in>>dpxp_section_header.tableNumber;

        return in;
    }
}MultSigleSelectHeadFram_t;


class PROTOCOLMANAGERSHARED_EXPORT MultSingleTableSelProtocol:public BaseProtocolInterface
{
public:
    MultSingleTableSelProtocol();

    bool getDisplayDataFromByteArry(QDataStream& dataStream,
                                            BaseFram_t&  baseHead,
                                            QVector<CommunicationParameterData_t>& vectorParameterData
                                            ) Q_DECL_OVERRIDE;


};


#endif // MULTSINGLETABLESELPROTOCOL_H
