#ifndef TBRAWDATA_H
#define TBRAWDATA_H

#include "tbbase.h"
#include "CommonDefine/commonprotocolstruct.h"
#include "CommonDefine/ddbtablestruct.h"

#define SEND_DATE               "sendDate"
#define SAMPLE_TIME             "sampleTime"
#define SAMPLE_SEQUENCE         "sampleSequence"
#define PARA_NUMBER             "paraNumber"
#define PARA_CODE_NUM           "paraCodeNumber"
#define PARA_FLAG               "paraFlag"
#define DATA_TYPE               "dataType"
#define DATA_VALUE_TYPE         "dataValueType"
#define TASK_ID                 "taskId"
#define PARA_CONTENT            "paraConTent"
#define PART                    "part"

class DATABASESHARED_EXPORT TbRawData : public TbBase
{
public:
    TbRawData(SqliteDatabase *dbbase);

    /**
    * @brief createTable 创建表
    * @param tableName 创建的表名称
    * @return true-成功；false-失败；
    */
    bool createTable();

    bool add(const CommunicationParameterData_t &values);

};

#endif // TBRAWDATA_H
