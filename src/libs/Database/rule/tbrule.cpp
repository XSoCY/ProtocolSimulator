#include "tbrule.h"

//表名
#define TABLE_NAME_INTERVAL         "rule_interval"             //上下限
#define TABLE_NAME_DIFF             "rule_diff"                 //差值
#define TABLE_NAME_TIME             "rule_time"                 //分时间区间（主表）
#define TABLE_NAME_TIME_INTERVAL    "rule_time_interval"        //分时间区间（上下限）
#define TABLE_NAME_TIME_DIFF        "rule_time_diff"            //分时间区间（差值）
#define TABLE_NAME_SEQUENCE         "rule_sequence"             //飞行时序
#define TABLE_NAME_SEQUENCE_DETAIL  "rule_sequence_detail"      //飞行时序详情

//字段名
#define FIELD_ID                    "id"                        //主键id   int
#define FIELD_TYPE                  "type"                      //类型: 0 差值, 1 上下限 tinyint
#define FIELD_MIN_VAL               "min"                       //最小值   double
#define FIELD_MAX_VAL               "max"                       //最大值   double
#define FIELD_INTERVAL              "interval"                  //间隔     int
#define FIELD_TABLE_NUM             "table_number"              //参数表号  int
#define FIELD_PARAM_ID              "param_id"                  //参数主键  int
#define FIELD_START_TABLE_NUM       "start_table_number"        //开始参数表号  int
#define FIELD_START_PARAM_ID        "start_param_id"            //开始参数主键  int
#define FIELD_STOP_TABLE_NUM        "stop_table_number"         //结束参数表号  int
#define FIELD_STOP_PARAM_ID         "stop_param_id"             //结束参数主键  int
#define FIELD_TIME_ID               "rule_time_id"              //分时间区间主表ID  int
#define FIELD_SORT                  "sort"                      //参数出现先后顺序
#define FIELD_SEQUENCE_ID           "sequence_id"               //飞行时序主表ID
#define FIELD_THEORY                "theory"                    //理论值
#define FIELD_ERROR                 "error"                     //误差范围

TbRule::TbRule(SqliteDatabase *dbbase)
    : TbBase(dbbase)
{

}

TbRule::~TbRule()
{

}

bool TbRule::getIntervalRule(st_UpLowDataRule_Map &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    TbBase::getRecords(TABLE_NAME_INTERVAL, "", records);

    foreach (QSqlRecord record, records)
    {
        st_UpLowDataRule temp;
        temp.min = record.value(FIELD_MIN_VAL).toDouble();
        temp.max = record.value(FIELD_MAX_VAL).toDouble();

        //根据参数表号(table_number) 和 参数主键(param_id) 生成: key
        int tbNum  = record.value(FIELD_TABLE_NUM).toInt();
        int paraId = record.value(FIELD_PARAM_ID).toInt();
        int key = (QString::number(tbNum) + QString::number(paraId)).toInt();

        ret.insert(key, temp);
    }

    return true;
}

bool TbRule::getDiffRule(st_DiffDataRule_Map &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    TbBase::getRecords(TABLE_NAME_DIFF, "", records);

    foreach (QSqlRecord record, records)
    {
        st_DiffDataRule temp;
        temp.min = record.value(FIELD_MIN_VAL).toDouble();
        temp.max = record.value(FIELD_MAX_VAL).toDouble();
        temp.interval = record.value(FIELD_INTERVAL).toInt();

        //根据参数表号(table_number) 和 参数主键(param_id) 生成: key
        int tbNum  = record.value(FIELD_TABLE_NUM).toInt();
        int paraId = record.value(FIELD_PARAM_ID).toInt();
        int key = (QString::number(tbNum) + QString::number(paraId)).toInt();

        ret.insert(key, temp);
    }

    return true;
}

bool TbRule::getTimeIntervalRule(st_tableParam_Map &startMap, st_tableParam_Map &stopMap, st_UpLowDataRule_Map &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    QString swhere = QString("WHERE %1 = %2").arg(FIELD_TYPE).arg(1);//类型: 0 差值, 1 上下限 tinyint
    TbBase::getRecords(TABLE_NAME_TIME, swhere, records);   //查分时间分区间(主表)中“上下限”类型记录

    foreach (QSqlRecord record, records)
    {
        //生成开始编号
        int tbNum  = record.value(FIELD_START_TABLE_NUM).toInt();
        int paraId = record.value(FIELD_START_PARAM_ID).toInt();
        int startNum = (QString::number(tbNum) + QString::number(paraId)).toInt();
        //生成结束编号
        tbNum  = record.value(FIELD_STOP_TABLE_NUM).toInt();
        paraId = record.value(FIELD_STOP_PARAM_ID).toInt();
        int stopNum = (QString::number(tbNum) + QString::number(paraId)).toInt();

        int mainId = record.value(FIELD_ID).toInt();    //主表的“主键id”对应从表的“分时间区间主表ID”
        QString swhere = QString("WHERE %1 = %2").arg(FIELD_TIME_ID).arg(mainId);
        QList<QSqlRecord> subRecords;
        //查询“分时间区间主表ID=主键id”的记录
        TbBase::getRecords(TABLE_NAME_TIME_DIFF, swhere, subRecords);
        st_UpLowDataRule temp;
        temp.min = subRecords.first().value(FIELD_MIN_VAL).toDouble();
        temp.max = subRecords.first().value(FIELD_MAX_VAL).toDouble();

        //根据参数表号(table_number) 和 参数主键(param_id) 生成: key
        tbNum  = subRecords.first().value(FIELD_TABLE_NUM).toInt();
        paraId = subRecords.first().value(FIELD_PARAM_ID).toInt();
        int key = (QString::number(tbNum) + QString::number(paraId)).toInt();

        startMap.insert(startNum, key);
        stopMap.insert(stopNum, key);
        ret.insert(key, temp);
    }

    return true;
}

bool TbRule::getTimeDiffRule(st_tableParam_Map &startMap, st_tableParam_Map &stopMap, st_DiffDataRule_Map &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    QString swhere = QString("WHERE %1 = %2").arg(FIELD_TYPE).arg(0);//类型: 0 差值, 1 上下限 tinyint
    TbBase::getRecords(TABLE_NAME_TIME, swhere, records);   //查分时间分区间(主表)中“差值”类型记录

    foreach (QSqlRecord record, records)
    {
        //生成开始编号
        int tbNum  = record.value(FIELD_START_TABLE_NUM).toInt();
        int paraId = record.value(FIELD_START_PARAM_ID).toInt();
        int startNum = (QString::number(tbNum) + QString::number(paraId)).toInt();
        //生成结束编号
        tbNum  = record.value(FIELD_STOP_TABLE_NUM).toInt();
        paraId = record.value(FIELD_STOP_PARAM_ID).toInt();
        int stopNum = (QString::number(tbNum) + QString::number(paraId)).toInt();

        int mainId = record.value(FIELD_ID).toInt();    //主表的“主键id”对应从表的“分时间区间主表ID”
        QString swhere = QString("WHERE %1 = %2").arg(FIELD_TIME_ID).arg(mainId);
        QList<QSqlRecord> subRecords;
        //查询“分时间区间主表ID=主键id”的记录
        TbBase::getRecords(TABLE_NAME_TIME_DIFF, swhere, subRecords);
        st_DiffDataRule temp;
        temp.min = subRecords.first().value(FIELD_MIN_VAL).toDouble();
        temp.max = subRecords.first().value(FIELD_MAX_VAL).toDouble();
        temp.interval = subRecords.first().value(FIELD_INTERVAL).toInt();

        //根据参数表号(table_number) 和 参数主键(param_id) 生成: key
        tbNum  = subRecords.first().value(FIELD_TABLE_NUM).toInt();
        paraId = subRecords.first().value(FIELD_PARAM_ID).toInt();
        int key = (QString::number(tbNum) + QString::number(paraId)).toInt();

        startMap.insert(startNum, key);
        stopMap.insert(stopNum, key);
        ret.insert(key, temp);
    }

    return true;
}

bool TbRule::getSequenceWireRule(st_SequenceDataRuleAll_Vector &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    QString swhere = QString("WHERE %1 = %2 ORDER BY %3 ASC")       //type飞行时序类型：0 无线，1 有线
                        .arg(FIELD_TYPE).arg(1).arg(FIELD_SORT);
    TbBase::getRecords(TABLE_NAME_SEQUENCE, swhere, records);       //查飞行时序主表(按sort排序)

    foreach (QSqlRecord record, records) {
        //根据参数表号(table_number) 和 参数主键(param_id) 生成: 主点编号
        int mainTbNum  = record.value(FIELD_TABLE_NUM).toInt();
        int mainParaId = record.value(FIELD_PARAM_ID).toInt();
        int mainPointNum = (QString::number(mainTbNum) + QString::number(mainParaId)).toInt();
        st_SequenceDataRuleAll_Pair mainPointData;
        int sequenceId = record.value(FIELD_ID).toInt();
        QString swhere = QString("WHERE %1 = %2").arg(FIELD_SEQUENCE_ID).arg(sequenceId);//查飞行时序详情表
        QList<QSqlRecord> detailRecords;
        TbBase::getRecords(TABLE_NAME_SEQUENCE_DETAIL, swhere, detailRecords);
        st_SequenceDataRule_Vector subPointVector;
        foreach (QSqlRecord detailRecord, detailRecords) {
            st_SequenceDataRule_Pair subPointData;
            //根据参数表号(table_number) 和 参数主键(param_id) 生成: 从点编号
            int subTbNum  = detailRecord.value(FIELD_TABLE_NUM).toInt();
            int subParaId = detailRecord.value(FIELD_PARAM_ID).toInt();
            int subPointNum = (QString::number(subTbNum) + QString::number(subParaId)).toInt();
            st_SequenceDataRule ruleData;
            ruleData.theory = detailRecord.value(FIELD_THEORY).toDouble();
            ruleData.error = detailRecord.value(FIELD_ERROR).toDouble();
            subPointData.first  = subPointNum;
            subPointData.second = ruleData;

            subPointVector.append(subPointData);
        }
        mainPointData.first  = mainPointNum;
        mainPointData.second = subPointVector;

        ret.append(mainPointData);
    }

    return true;
}

bool TbRule::getSequenceWirelessRule(st_SequenceDataRuleAll_Vector &ret)
{
    if( !getDatabase() ) return false;
    if( !getDatabase()->isSqlDataBaseValid() ) return false;

    QList<QSqlRecord> records;
    QString swhere = QString("WHERE %1 = %2 ORDER BY %3 ASC")       //type飞行时序类型：0 无线，1 有线
                        .arg(FIELD_TYPE).arg(0).arg(FIELD_SORT);
    TbBase::getRecords(TABLE_NAME_SEQUENCE, swhere, records);       //查飞行时序主表(按sort排序)

    foreach (QSqlRecord record, records) {
        //根据参数表号(table_number) 和 参数主键(param_id) 生成: 主点编号
        int mainTbNum  = record.value(FIELD_TABLE_NUM).toInt();
        int mainParaId = record.value(FIELD_PARAM_ID).toInt();
        int mainPointNum = (QString::number(mainTbNum) + QString::number(mainParaId)).toInt();
        st_SequenceDataRuleAll_Pair mainPointData;
        int sequenceId = record.value(FIELD_ID).toInt();
        QString swhere = QString("WHERE %1 = %2").arg(FIELD_SEQUENCE_ID).arg(sequenceId);//查飞行时序详情表
        QList<QSqlRecord> detailRecords;
        TbBase::getRecords(TABLE_NAME_SEQUENCE_DETAIL, swhere, detailRecords);
        st_SequenceDataRule_Vector subPointVector;
        foreach (QSqlRecord detailRecord, detailRecords) {
            st_SequenceDataRule_Pair subPointData;
            //根据参数表号(table_number) 和 参数主键(param_id) 生成: 从点编号
            int subTbNum  = detailRecord.value(FIELD_TABLE_NUM).toInt();
            int subParaId = detailRecord.value(FIELD_PARAM_ID).toInt();
            int subPointNum = (QString::number(subTbNum) + QString::number(subParaId)).toInt();
            st_SequenceDataRule ruleData;
            ruleData.theory = detailRecord.value(FIELD_THEORY).toDouble();
            ruleData.error = detailRecord.value(FIELD_ERROR).toDouble();
            subPointData.first  = subPointNum;
            subPointData.second = ruleData;

            subPointVector.append(subPointData);
        }
        mainPointData.first  = mainPointNum;
        mainPointData.second = subPointVector;

        ret.append(mainPointData);
    }

    return true;
}
