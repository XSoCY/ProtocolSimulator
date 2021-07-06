#ifndef TBRULE_H
#define TBRULE_H

#include "tbbase.h"
#include "CommonDefine/ddbtablestruct.h"

//数据库中判读规则相关表的类型
enum RuleTableType {
    Rule_Interval,          //上下限
    Rule_Diff,              //差值
    Rule_Time,              //分时间区间（主表）
    Rule_Time_Interval,     //分时间区间（上下限）
    Rule_Time_Diff,         //分时间区间（差值）
    Rule_Sequence,          //飞行时序
    Rule_Sequence_Detail    //飞行时序详情
};

class DATABASESHARED_EXPORT TbRule : public TbBase
{
public:
    TbRule(SqliteDatabase *dbbase);
    ~TbRule();

    /**
     * @brief getIntervalRule       获取上下限判读规则
     * @param ret   判读规则数据
     * @return true:成功; false:失败
     */
    bool getIntervalRule(st_UpLowDataRule_Map &ret);

    /**
     * @brief getDiffRule           获取差值判读规则
     * @param ret   判读规则数据
     * @return true:成功; false:失败
     */
    bool getDiffRule(st_DiffDataRule_Map &ret);

    /**
     * @brief getTimeIntervalRule   获取分时分区上下限判读规则
     * @param startMap
     * @param stopMap
     * @param ret
     * @return
     */
    bool getTimeIntervalRule(st_tableParam_Map &startMap, st_tableParam_Map &stopMap, st_UpLowDataRule_Map &ret);

    /**
     * @brief getTimeDiffRule       获取分时分区差值判读规则
     * @param startMap
     * @param stopMap
     * @param ret
     * @return
     */
    bool getTimeDiffRule(st_tableParam_Map &startMap, st_tableParam_Map &stopMap, st_DiffDataRule_Map &ret);

    /**
     * @brief getSequenceWireRule   获取飞行时序(有线)判读规则
     * @param ret
     * @return
     */
    bool getSequenceWireRule(st_SequenceDataRuleAll_Vector &ret);

    /**
     * @brief getSequenceWireRule   获取飞行时序(无线)判读规则
     * @param ret
     * @return
     */
    bool getSequenceWirelessRule(st_SequenceDataRuleAll_Vector &ret);
};

#endif // TBRULE_H
