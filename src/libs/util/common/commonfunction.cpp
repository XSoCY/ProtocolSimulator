#include "commonfunction.h"
#include <QString>
#include <QStringList>


CommonFunction::CommonFunction(QObject *parent)
    : QObject(parent)
{

}

QString CommonFunction::getDeviceIdentifyId(quint16 deviceID, quint8 snNum)
{
    return QString("%1_%2").arg((uint)deviceID).arg((uint)snNum);
}

bool CommonFunction::getDeviceIdentifyId(const QString &identifyID, quint16 &deviceID, quint8 &snNum)
{
    QString idenID = identifyID;
    if(!idenID.contains("_"))
    {
        return false;
    }
    QStringList items = idenID.split("_");
    if(items.size() < 2)
    {
        return false;
    }
    QString strDevID =items[0];
    QString strSnNum =items[1];

    deviceID = strDevID.toShort();
    snNum = strSnNum.toInt();
    return true;
}


void CommonFunction::getIDFromMemID(const quint64 memID,
                                    ushort &usStationID,
                                    uchar &ucSubSysID,
                                    ushort &usDeviceID,
                                    ushort &usType,
                                    uchar &ucSn)
{

    //    quint64 ui64ID = 0;
    //    ui64ID = ((((quint64)usStationID & 0xFFFF) << 48) + (((quint64)ucSubSysID & 0xFF) << 40)
    //              + (((quint64)usDeviceID & 0xFFFF) << 24) + (((quint64)usType & 0xFFFF) << 8)
    //              + ((quint64)ucSn & 0xFF));

    usStationID = memID >> 48;
    ucSubSysID  = memID >> 40;
    usDeviceID  = memID >> 24;
    usType      = memID >> 8;
    ucSn        = memID;
}

/**
 * @brief getModeFromParamblockID 获取设备模式来至于参数块ID
 * @param paramBlockId  参数块ID
 * @param ucMode        设备模式
 */
void CommonFunction::getModeFromParamblockID(const quint64 paramBlockId, uchar &ucMode)
{
    ucMode = paramBlockId >> 40;
}

void CommonFunction::getDeviceIDFromMemID(const quint64 memId, ushort &deviceID)
{
    deviceID  = memId >> 24;
}

void CommonFunction::getTidFromMemID(const quint64 memId, ushort &Tid)
{
    Tid      = memId >> 8;
}

quint32 CommonFunction::getVerifyCrc32(const quint8 *pbySrc_IN, const quint32 dwLength_IN)
{
    if( (NULL==pbySrc_IN)||(0==dwLength_IN) )
        return 0;

    // 初始化CRC表
    static quint32 s_adwCrcTbl[256];
    static quint32 If_HadInitCrcTbl=0;
    if( 0==If_HadInitCrcTbl )
    {
        Crc32Initcrctable( s_adwCrcTbl );
        if( 0!=s_adwCrcTbl[1] )
        {
            If_HadInitCrcTbl = 1;
        }
        else
        {
            // 无法继续完成CRC
            return 0;
        }
    }

    quint32 dwCrc = 0;
    quint8* pbySrc = (quint8 *)pbySrc_IN;
    for( quint32 i=0; i<dwLength_IN; i++ )
    {
        dwCrc = ((dwCrc>>8) & 0x00FFFFFF) ^ s_adwCrcTbl[(quint8)(dwCrc^*pbySrc++)];
    }
    return dwCrc;
}

int CommonFunction::changeCharComplementToInt(char charData)
{
    int retInt = charData;
    if(retInt > 128)
    {
        retInt = 0xffffff00 + charData;
    }
    return retInt;
}

void CommonFunction::Crc32Initcrctable(quint32 *pCrcTable)
{
    if( pCrcTable[1] )
        return;

    const quint32 c_dwCRC32_POLYNOMIAL = 0xEDB88320;

    quint32 dwCrc = 0;
    for( quint32 i=0; i<256; ++i )
    {
        dwCrc = i;

        for( quint32 j=8; j>0; --j )
        {
            if( dwCrc&1 )
            {
                dwCrc = (dwCrc>>1)^c_dwCRC32_POLYNOMIAL;
            }
            else
            {
                dwCrc >>= 1;
            }
        }

        pCrcTable[i] = dwCrc;
    }
}

