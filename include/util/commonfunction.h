#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include <QObject>
#include "util_global.h"

class UTILSHARED_SELF_EXPORT CommonFunction : public QObject
{
    Q_OBJECT
public:
    explicit CommonFunction(QObject *parent = nullptr);

public:
    //获取设备对应的唯一id(设备号_流号)
    static  QString getDeviceIdentifyId(quint16 deviceID, quint8 snNum);
    //获取设备id获取设备类型流号(设备号,流号)
    static bool getDeviceIdentifyId(const QString& identifyID, quint16& deviceID, quint8& snNum);
    //分解网络id
    static void getIDFromMemID(const quint64 memID,
                               ushort& usStationID,
                               uchar& ucSubSysID,
                               ushort& usDeviceID,
                               ushort& usType,
                               uchar& ucSn);
    //获取设备ID
    static void getDeviceIDFromMemID(const quint64 memId, ushort& deviceID);
    //获取TID
    static void getTidFromMemID(const quint64 memId, ushort &Tid);
    /**
     * @brief getModeFromParamblockID 获取设备模式来至于参数块ID
     * @param paramBlockId  参数块ID
     * @param ucMode        设备模式
     */
    static void getModeFromParamblockID(const quint64 paramBlockId, uchar &ucMode);
    //获取32位CRC校验算法值
    static  quint32 getVerifyCrc32( const quint8* pbySrc_IN, const quint32 dwLength_IN );

    //char补码转int补码
    static int changeCharComplementToInt(char charData);
private:
    static void Crc32Initcrctable( quint32 *pCrcTable );
signals:

public slots:
};

#endif // COMMONFUNCTION_H
