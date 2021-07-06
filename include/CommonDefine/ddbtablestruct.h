#ifndef DBTABLESTRUCT_H
#define DBTABLESTRUCT_H
#include <QString>
#include <QVector>
#include <qmetatype.h>

//##### 上下限规则表对应的数据结构
typedef struct st_UpLowDataRule_
{
    float min;//最小值
    float max;//最大值
    bool  flag;//标志，true进行判读，false不判读
    st_UpLowDataRule_()
    {
        min = 0.0;
        max = 0.0;
        flag = true;
    }
}st_UpLowDataRule;
//map关键字为 table_number参数表表号 + param_id参数表主键
//eg table_number=1081 ; param_id = 1   key = 18011
typedef QMap<int, st_UpLowDataRule> st_UpLowDataRule_Map;

//##### 差值规则表对应的数据结构
typedef struct st_DiffDataRule_
{
    int interval;//间隔
    float min;//最小值
    float max;//最大值
    bool  flag;//标志，true进行判读，false不判读
    st_DiffDataRule_()
    {
        interval =0;
        min = 0.0;
        max = 0.0;
        flag = true;
    }
}st_DiffDataRule;
//map关键字为 table_number参数表表号 + param_id参数表主键
//eg table_number=1081 ; param_id = 1   key = 18011
typedef QMap<int, st_DiffDataRule> st_DiffDataRule_Map;

//存放上一次差值判读的值
typedef struct D_LastValue_
{
    float value;
    quint16 times;
    D_LastValue_()
    {
        value = 0.0;
        times = 0;
    }
}D_LastValue;
typedef QMap<int, D_LastValue> st_LastDiffDataRule_Map;

//##### 飞行时序规则表对应的数据结构
typedef struct st_SequenceDataRule_
{

    float theory;//理论值
    float error;//误差范围
    st_SequenceDataRule_()
    {
        theory = 0.0;
        error = 0.0;
    }
}st_SequenceDataRule;
Q_DECLARE_METATYPE(st_SequenceDataRule)//供一个默认的拷贝构造函数
//map关键字为 table_number参数表表号 + param_id参数表主键
//eg table_number=1081 ; param_id = 1   key = 18011
typedef QPair<int, st_SequenceDataRule> st_SequenceDataRule_Pair;
typedef QVector<st_SequenceDataRule_Pair> st_SequenceDataRule_Vector;

//map关键之为开始编号  或者 结束编号  value 为关联的编号
typedef QMap<int, int> st_tableParam_Map;
//第一个参数为，主点编号
typedef QPair<int,st_SequenceDataRule_Vector> st_SequenceDataRuleAll_Pair;
typedef QVector<st_SequenceDataRuleAll_Pair> st_SequenceDataRuleAll_Vector;
//关于查询表结构的输出说明，以及定义
//1,单独上下限判读 输出st_UpLowDataRule_Map   初始值：flag = true;
//2,单独差值判读   输出st_DiffDataRule_Map    初始值：flag = true
//3,分时分区上下限判读  输出1， st_tableParam_Map开始map  输出2 st_tableParam_Map结束map 输出3 st_UpLowDataRule_Map上下限  初始值：flag = false
//4,分时分区差值判读  输出1， st_tableParam_Map开始map  输出2 st_tableParam_Map结束map 输出3 st_DiffDataRule_Map差值     初始值：flag = false
//5,飞行时序(有线)   输出1：st_SequenceDataRuleAll_Vector 注意主点编号根据sort排序，***从点是否根据间隔排序，暂不考虑
//6,飞行时序(无线)   输出1：st_SequenceDataRuleAll_Vector 注意主点编号根据sort排序，***从点是否根据间隔排序，暂不考虑


#endif  // DBTABLESTRUCT_H
