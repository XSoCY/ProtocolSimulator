/*
 *　Copyright (c)　2015,成都能通科技有限公司
 *　All rights reserved.
 *
 *　文件名称：cconverter.h
 *　文件标识：见配置管理计划书
 *　摘要：该文件对CConverter类的和相应的成员及方法进行了定义。
 *       CConverter类为数据转换类，向外界提供各种数据类型间转换的方法。
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <qglobal.h>
#include "util_global.h"

class QBitArray;
class QByteArray;
class QString;

class UTILSHARED_SELF_EXPORT CConverter
{

public:
    CConverter();

public:
    static int byteToInt(QByteArray byteArr);
    static uint byteToUInt(QByteArray byteArr);
    static double byteToDouble(QByteArray byteArr);
    static float byteToFloat(QByteArray byteArr);
    static int8_t byteToInt8(QByteArray byteArr);
    static uint8_t byteToUInt8(QByteArray byteArr);
    static ushort byteHexToUshortDec(QByteArray byteArr);
    static int getDEC_IN_BIN(int num, int index);
    static void IPToUint(QString stringIP, unsigned int &ip);

    static ushort byteToUshort(QByteArray byteArr);
    static short byteToShort(QByteArray byteArr);
    static char byteToChar(QByteArray byteArr);
    static uchar byteToUChar(QByteArray byteArr);
    static QString byteToString(QByteArray byteArr);
    static qint64 byteToQInt64(QByteArray byteArr);
    static quint64 byteToQUInt64(QByteArray byteArr);
    static void byteToBinary(QByteArray byteArr, int* binary);
    static QString charToTime(char* data);
    static void uintToIP(const unsigned int ip,char *stringIP);

    static QByteArray int8ToByte(int8_t target);
    static QByteArray uint8ToByte(uint8_t target);
    static QByteArray intToByte(int target);
    static QByteArray uintToByte(uint target);
    static QByteArray doubleToByte(double target);
    static QByteArray floatToByte(float target);
    static QByteArray ushortToByte(ushort target);
    static QByteArray shortToByte(short target);
    static QByteArray charToByte(char target);
    static QByteArray ucharToByte(uchar target);
    static QByteArray stringToByte(QString target);
    static QByteArray qint64ToByte(qint64 target);
    static QByteArray quint64ToByte(quint64 target);
    static QByteArray binaryToByte(int* binary, int length);
    static QByteArray bitArrayToBytes(const QBitArray &bitArr);

    /*!
     * \brief complementToChar二进制补码转char
     * \param sourData：需要转的二进制数
     * \return 返回char值
     */
    static char complementToChar(char sourData);

    /*!
     * \brief charToComplement:二进制值转补码
     * \param sourData
     * \return
     */
    static char charToComplement(char sourData);

    /**
     * @brief bitArrayToInt
     * 比特位数组转成int型，调用前需为bitArr进行内存分配
     * @param bitArr int型的数组，里面存放0或1，表示每个比特位值
     * @param bitLength bitArr数组长度
     * @return int型数据
     */
    static int bitArrayToInt(int bitArr[], int bitLength);
    /**
     * @brief intToBitArray
     * 将一个int型数据装成bit位数组，返回的ret需在调用前分配内存
     * @param value 需转的int型数据
     * @param length ret数组的长度
     * @param ret 输出参数 输出一个int型数组，存放表示value的bit位数据
     */
    static void intToBitArray(int value, int length, int* ret);
    // QByteArray转16进制字符串//add
    static QString byteArrayToHexString(QByteArray data);

    // 16进制转QByteArray
    static QByteArray hexToByteArray(QString data);

    //十位数转BCD码//add
    static short tenDigitNumberToBCD(short tensNumber);

    // QByteArray内部字节反转
    static QByteArray qByteArrayReverse(QByteArray message, int byteNumber);

    /**
     * @brief hexToShort 16进制字符串转short
     * @param data 需转short类型的16进制串，长度必须是5；
     * @param ret 返回转换后的short
     */
    static bool hexToShort(const char* data, short &value);

    /**
     * @brief ushortToHexString 将ushort转成16进制串
     * @param data 需转short类型的16进制串，长度必须是5；
	 * @param bHighLow 是否高低字节转换（要与设备显示相同，所以需要高低字节转换）；
     * @param ret 返回转换后的字符串
     */
    static QString ushortToHexString(ushort data, bool bHighLow = true);

private:
    static char* byteToPChar(QByteArray& byteArr, int length);
};

#endif  // CONVERTER_H
