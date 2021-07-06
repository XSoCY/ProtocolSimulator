#ifndef COMMONPROTOCOLSTRUCT_H
#define COMMONPROTOCOLSTRUCT_H

#include <QByteArray>
#include <QDataStream>

//*************************************协议相关************************************************

//数据源
enum SIDType{
    sourceAdminTerminalType = 0x00,//管理终端
    SourceJudgetType = 0x01, //判读软件
    SourceWebServerType = 0x10,//web服务端
};
//数据目的地
enum DIDType{
    destAdminTerminalType = 0x00,//管理终端
    destJudgetType = 0x01, //判读软件
    destWebServerType = 0x10,//web服务端
};

//代表不同协议解析对象
enum ProtocolType{
     MultSingleTableSel = 0x01, //多单表挑点

};
//消息发送类型
enum MessageType
{
    MessageOrignalType              =  0xFEEF,  //原始数据
    MessageTaskType                 =  0xDFFD,  //任务通知类型数据
    MessageJudgeLimitType           =  0xEFFE,  //判读数据上下限
    MessageJudgeStatusType          =  0xEFFD,  //判读数据状态
    MessageJudgeTimeAndSectionType  =  0xEFFC,  //判读数据分时分区
    MessageJudgeDifferentType       =  0xEFFB,  //判读数据差值
    MessageJudgeFlightTimeFitting   =  0xEFFA,  //判读数据飞行时序拟合
};

enum paraDataValueType{
    ParamBYTEType = 0x00,
    ParamFLOATType = 0x01,
};
#pragma pack(1)

/*
 * 基本帧结构体
 */
typedef struct BaseFram
{
    quint16 head ;          ///帧头：标识一个帧的开始，固定值：0x4E4A
    quint16 dataLength;           ///数据长度：为数据域的长度
    quint8 SID;           ///SID：数据源，标识由谁发出的
    quint8 DID;           ///DID：数据目的地，数据是发给谁的
    quint8 type;    ///Type：数据用途，指本帧数据是干什么用的

    friend QDataStream& operator <<(QDataStream& out, const BaseFram& baseFramStruct)
    {
        out<<baseFramStruct.head;
        out<<baseFramStruct.dataLength;
        out<<baseFramStruct.SID;
        out<<baseFramStruct.DID;
        out<<baseFramStruct.type;

        return out;
    }
    friend QDataStream& operator >>(QDataStream& in, BaseFram& baseFramStruct)
    {
        in>>baseFramStruct.head;
        in>>baseFramStruct.dataLength;
        in>>baseFramStruct.SID;
        in>>baseFramStruct.DID;
        in>>baseFramStruct.type;
        return in;
    }
}BaseFram_t;

/*
 * 子数据段帧头格式
 */
typedef struct SubFrameHead
{
    quint8  paramType;      //参数类型 0x00---数值型参数；float 4字节   0x01---状态型参数；BYTE 1字节
    quint32 time;           //子段时间
    quint16 length;         //子段长度
    quint16 tableNum;       //表号

    SubFrameHead() {
        paramType   = 0x01;
        time        = 0;
        length      = 0;
    }

    friend QDataStream& operator <<(QDataStream &out, const SubFrameHead &subFramStruct) {
        out << subFramStruct.paramType;
        out << subFramStruct.time;
        out << subFramStruct.length;
        out << subFramStruct.tableNum;

        return out;
    }

    friend QDataStream& operator >>(QDataStream &in, SubFrameHead &subFramStruct) {
        in >> subFramStruct.paramType;
        in >> subFramStruct.time;
        in >> subFramStruct.length;
        in >> subFramStruct.tableNum;

        return in;
    }
}SubFrameHead_t;

/*
 * 参数数据结构
 */
typedef struct CommunicationParameterData{
    quint16 sendDate;       //发送日期，相对2000.1.1，累加天数
    quint32  sampleTime;    //采集时间
    quint16 paraNumber;     //参数表号
    quint16 paraCodeNumber; //参数编码
    quint32 dataType;       ///参数类型，原始数据：BASEFRAM_ORIGINAL_TYPE；判断数据：BASEFRAM_JUDGE_TYPE
    quint8 sourID; ///传输数据的源地址：
    quint8 destID; ///传输数据的源地址：
    quint8 dataValueType;   //参数值类型；数据值类型Byte：0x01；数据值类型float：0x02
    QByteArray paraConTent; //参数内容
}CommunicationParameterData_t;

#pragma pack()


#endif // COMMONPROTOCOLSTRUCT_H










