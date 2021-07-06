#include "multsingletableselprotocol.h"
#include "baseprotocolinterface.h"
MultSingleTableSelProtocol::MultSingleTableSelProtocol()
{

}

bool MultSingleTableSelProtocol::getDisplayDataFromByteArry(QDataStream &dataStream, BaseFram_t &baseHead, QVector<CommunicationParameterData_t> &vectorParameterData)
{
    //参数序号 + 参数 + 超差标识
    quint16 mParaCodeNumber;//参数序号
    //参数
    quint8  mByteData;//Byte参数
    float  mFloatData;//float参数
    quint8 mOverFlag;//超差标识
    quint16 subSegTail = 0xffff;//子段尾
    int sizeOfTail = sizeof(subSegTail);//子段尾字节数
    while(!dataStream.atEnd())
    {
        //获取头
        MultSigleSelectHeadFram_t multSigleHead;
        dataStream >> multSigleHead;
        int subLen = multSigleHead.subLength;//子段长
        int readLen = 0;
        while(readLen <= (subLen - sizeOfTail))
        {
            CommunicationParameterData_t mParameterData;
            mParameterData.paraNumber = multSigleHead.tableNumber;
            mParameterData.dataType = MessageOrignalType;//原始数据
            mParameterData.sourID = sourceAdminTerminalType;//管理终端
            mParameterData.destID = destJudgetType; //判读软件
            dataStream >> mParaCodeNumber;//>>参数序号
            mParameterData.paraCodeNumber = mParaCodeNumber;
            readLen += sizeof(mParaCodeNumber);
            //>>参数
            if(multSigleHead.paraType == ParamBYTEType)
            {
                dataStream >> mByteData;
                readLen += sizeof(mByteData);
                mParameterData.dataValueType = ParamBYTEType;
                mParameterData.paraConTent.append(QByteArray::number(mByteData));
            }
            else if(multSigleHead.paraType == ParamFLOATType){
                dataStream >> mFloatData;
                readLen += sizeof(mFloatData);
                mParameterData.dataValueType = ParamFLOATType;
                mParameterData.paraConTent.append(QByteArray::number(mFloatData, 'f', 3));
            }
            dataStream >> mOverFlag; //超差标识
            readLen += sizeof(mOverFlag);

            if(mParameterData.paraNumber != 0)
            {
                vectorParameterData.append(mParameterData);
            }
        }
        dataStream >> subSegTail;//子段尾
    }
    return true;
}
