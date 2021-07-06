#ifndef COMMUNICATION_DEFINE_H
#define COMMUNICATION_DEFINE_H


//通道id
#define CHANNEL_ID_Equipment                "Equipment"
#define CHANNEL_ID_TTCCombination           "TTCCombination"
#define CHANNEL_ID_TTCFrontCompter          "TTCFrontCompter"


//设备类型
enum EquipmentType{
//    JudgetSoft = 0x00, //判读软件
//    TTCcombination = 0x01,//测发控组合
//    TTCFrontComputerForm = 0x02,//测发控前端计算机
//    PARAEquipment = 0x03,//参数管理终端
//    WebServerSoft = 0x04,//web服务端


       DISTRIBUTOR = 0x01,//(1, "配电器"),
       ROCKET_MACHINE = 0x02,//(2, "箭机"),
       MEASURE_GROUP = 0x03,//(3, "一体化测量组合")
       POWER_1 = 0x11,//(17, "电源1"),
       POWER_2 = 0x12,//(18, "电源2"),
       POWER_3 = 0x13,//(19, "电源3"),
       POWER_4 = 0x15,//(21, "电源4"),
       POWER_5 = 0x16,//(22, "电源5"),
       TLC_FRONT_END = 0x17,//(23, "测发控前端计算机"),
       SYNTHESIS_CONTROL_COMPUTER = 0x18,//(24, "综合控制计算机"),
       TLC_GROUP = 0x19,//(25, "测发控组合"),
       TEACH_CONTROL_COMPUTER = 0x21,//(33, "教学管控计算机"),
       SERVER = 0x22 ,//(34, "服务器"),

};
enum FrameType{
    UpType = 0x00,
    DownType = 0xFF,
};

#endif // COMMUNICATION_DEFINE_H
