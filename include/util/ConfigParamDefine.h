#ifndef CONFIGPARAMDEFINE_H
#define CONFIGPARAMDEFINE_H

#include "QObject"

/**
 * @brief DataType 数据类型枚举
 */
enum DataType
{
    DataType_Invalid = -1,      //无效
    DataType_char,              //1字节字符
    DataType_uchar,             //1字节无符号字符
    DataType_short,             //2字节整型
    DataType_ushort,            //2字节无符号整型
    DataType_int,               //4字节整型
    DataType_uint,              //4字节无符号整型
    DataType_int64,             //8字节整型
    DataType_uint64,            //8字节无符号整型
    DataType_Hex,               //16进制数据
    DataType_Bit,               //按位存取
    DataType_IP,                //IP数据
    DataType_Text,          //字符串
};

/**
 * @brief WidgetType 控件类型枚举
 */
enum WidgetType
{
    WidgetType_Invalid = -1,    // 无效
    WidgetType_ComboBox,        // 下拉框
    WidgetType_SpinBox,         // 选值框
};

/**
* @brief ParamItem 可配置参数项定义结构体
*/
//struct ParamItem
//{
//    QString paramID;            //参数id
//    QString label;              //参数标签名
//    QString widgetType;         //控件类型
//    QString dataType;           //数据类型
//    QString inputProperty;      //参数输入属性名
//    QString defaultValue;       //默认值
//    QString curValue;           //当前值
//    QString min;                //最小值
//    QString max;                //最大值
//    QString coefficient;        //系数(设置spinbox控件步长)
//    QString decimal;            //保留小数位数

//    ParamItem()
//    {
//        paramID = "";
//        label = "";
//        widgetType = "";
//        dataType = "";
//        inputProperty = "";
//        defaultValue = "";
//        curValue = "";
//        min = "";
//        max = "";
//        coefficient = "";
//        decimal = "";
//    }
//};

struct ParamItem
{
    char paramID[16];            //参数id
    char label[32];              //参数标签名
    char widgetType[16];         //控件类型
    char dataType[16];           //数据类型
    char inputProperty[16];      //参数输入属性名
    char defaultValue[32];       //默认值
    char curValue[32];           //当前值
    char min[32];                //最小值
    char max[32];                //最大值
    char coefficient[32];        //系数(设置spinbox控件步长)
    char decimal[2];             //保留小数位数

    ParamItem()
    {
        memset(this, 0, sizeof(ParamItem));
    }
};

#endif // CONFIGPARAMDEFINE_H
