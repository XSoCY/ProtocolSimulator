/*
 *　Copyright (c)　2015,成都能通科技有限公司
 *　All rights reserved.
 *
 *　文件名称：cconverter.cpp
 *　文件标识：见配置管理计划书
 *　摘要：该文件实现了头文件中CConverter类定义的方法。
 */

#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <qendian.h>
#include <QBitArray>

#include "CConstants.h"
#include "CConverter.h"
#include <stdio.h>

CConverter::CConverter() {}

/**
 * @brief Converter::byteToInt
 * 字节数组转整型
 * @param byteArr 字节数组
 * @return int型数据
 */
int CConverter::byteToInt(QByteArray byteArr)
{
    int sizeOfInt = CConstants::SIZE_OF_INT;

    char* pcharValue = byteToPChar(byteArr, sizeOfInt);

    if (pcharValue == NULL)
    {
        return 0;
    }

    int iValue = 0;
    //将字符数组强制转为int
    iValue = *((int*)pcharValue);
    return iValue;
}

/**
 * @brief byteToUInt
 * 字节数组转无符号整型
 * @param byteArr 字节数组
 * @return 无符号int
 */
uint CConverter::byteToUInt(QByteArray byteArr)
{
    int sizeOfInt = CConstants::SIZE_OF_INT;

    char* pcharValue = byteToPChar(byteArr, sizeOfInt);

    if (pcharValue == NULL)
    {
        return 0;
    }

    uint iValue = 0;
    //将字符数组强制转为int
    iValue = *((uint*)pcharValue);
    return iValue;
}

/**
 * @brief Converter::byteToDouble
 * 字节数组转double
 * @param byteArr 字节数组
 * @return double型数据
 */
double CConverter::byteToDouble(QByteArray byteArr)
{
    //获取当前操作系统double型的字节长度
    int sizeOfDouble = CConstants::SIZE_OF_DOUBLE;

    char* pcharValue = byteToPChar(byteArr, sizeOfDouble);

    if (pcharValue == NULL)
    {
        return 0.0;
    }

    double dValue = 0.0;
    //将字符数组强转为double
    dValue = *((double*)pcharValue);
    return dValue;
}

/**
 * @brief CConverter::byteToFloat
 * 字节数组转float
 * @param byteArr 字节数组
 * @return float型数据
 */
float CConverter::byteToFloat(QByteArray byteArr)
{
    int sizeOfFloat = CConstants::SIZE_OF_FLOAT;

    char* pcharValue = byteToPChar(byteArr, sizeOfFloat);

    if (pcharValue == NULL)
    {
        return 0.0f;
    }

    float fValue = 0.0f;
    //将字符数组强制转为float
    fValue = *((float*)pcharValue);
    return fValue;
}

int8_t CConverter::byteToInt8(QByteArray byteArr)
{
    int sizeOfInt8 = CConstants::SIZE_OF_INT8;
    char* pcharValue = byteToPChar(byteArr, sizeOfInt8);

    if (pcharValue == NULL)
    {
        return 0;
    }

    int8_t sValue = 0;
    sValue = *((int8_t*)pcharValue);

    return sValue;
}

uint8_t CConverter::byteToUInt8(QByteArray byteArr)
{
    int sizeOfUInt8 = CConstants::SIZE_OF_INT8;
    char* pcharValue = byteToPChar(byteArr, sizeOfUInt8);

    if (pcharValue == NULL)
    {
        return 0;
    }

    uint8_t sValue = 0;
    sValue = *((uint8_t*)pcharValue);

    return sValue;
}

ushort CConverter::byteHexToUshortDec(QByteArray byteArr)
{
    ushort usValue = 0;

    int iLen = byteArr.size();

    char s[80],str[80];
    memcpy( s, byteArr.data(), iLen);

    int m=0;

    for(int i = 0; i < iLen; i++)
    {
        if( (s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f')||(s[i]>='A'&&s[i]<='F') )
        {
            if( ( i == iLen - 1 && s[i] == '0' ) || s[i] == '\0' )
            {
                break;
            }
            str[m]=s[i];
            m++;
        }
        else
        {
            return usValue;
        }
    }

    str[m]='\0';
    for(int i=0;str[i]!='\0';i++)//将十六进制字符转换成十进制数
    {
        if(str[i]>='0'&&str[i]<='9')
        usValue=usValue*16+str[i]-'0';
        else if(str[i]>='a'&&str[i]<='f')
        usValue=usValue*16+str[i]-'a'+10;
        else if(str[i]>='A'&&str[i]<='F')
        usValue=usValue*16+str[i]-'A'+10;
    }

    return usValue;
}

int CConverter::getDEC_IN_BIN(int num, int index)
{
    return (num & (0x1 << index)) >> index;
}

void CConverter::IPToUint(QString stringIP, unsigned int &ip)
{
    uchar *tmp = (uchar*)&ip;
        QStringList lst = stringIP.split(".");
        if( lst.size() != 4 ) return;
        for(int i=0; i<4; ++i)
        {
            QString s = lst.at(i);
            tmp[i] = s.toInt();
        }
}

/**
 * @brief CConverter::byteToShort
 * 字节数组转ushort
 * @param byteArr
 * @return
 */
ushort CConverter::byteToUshort(QByteArray byteArr)
{
    int sizeOfShort = CConstants::SIZE_OF_SHORT;
    char* pcharValue = byteToPChar(byteArr, sizeOfShort);

    if (pcharValue == NULL)
    {
        return 0;
    }

    ushort sValue = 0;
    sValue = *((ushort*)pcharValue);
    return sValue;
}

/**
 * @brief CConverter::byteToShort
 * 字节数组转short
 * @param byteArr
 * @return
 */
short CConverter::byteToShort(QByteArray byteArr)
{
    int sizeOfShort = CConstants::SIZE_OF_SHORT;
    char* pcharValue = byteToPChar(byteArr, sizeOfShort);

    if (pcharValue == NULL)
    {
        return 0;
    }

    short sValue = 0;
    sValue = *((short*)pcharValue);
    return sValue;
}

/**
 * @brief byteToChar
 * 字节数组转char
 * @param byteArr
 * @return
 */
char CConverter::byteToChar(QByteArray byteArr)
{
    //判断字节数组长度
    if (byteArr.size() == 0)
    {
        return 0;
    }

    //字节数组长度不为0，直接取字节数组的第一个字符返回
    return byteArr.at(0);
}

/**
 * @brief CConverter::byteToUChar
 * 字节数组转uchar
 * @param byteArr
 * @return
 */
uchar CConverter::byteToUChar(QByteArray byteArr)
{
    //判断字节数组长度
    if (byteArr.length() == 0)
    {
        return 0;
    }

    //字节数组长度不为0，直接取字节数组的第一个字符返回
    return byteArr.at(0);
}

/**
 * @brief CConverter::byteToString
 * 字节数组转字符串
 * @param byteArr 字节数组
 * @return 字符串
 */
QString CConverter::byteToString(QByteArray byteArr)
{
    QString ret(byteArr);
    return ret;
}

/**
 * @brief CConverter::byteToLongLong
 * 字节数组转长整型
 * @param byteArr
 * @return
 */
qint64 CConverter::byteToQInt64(QByteArray byteArr)
{
    int sizeOfLong = CConstants::SIZE_OF_QINT64;

    char* pcharValue = byteToPChar(byteArr, sizeOfLong);

    if (pcharValue == NULL)
    {
        return -1;
    }

    qint64 value = -1;
    //将字符数组强制转为long
    value = *((qint64*)pcharValue);
    return value;
}

/**
 * @brief CConverter::byteToUInt64
 * 字节数组转无符号长整型
 * @param byteArr
 * @return
 */
quint64 CConverter::byteToQUInt64(QByteArray byteArr)
{
    int sizeOfLong = CConstants::SIZE_OF_QINT64;

    char* pcharValue = byteToPChar(byteArr, sizeOfLong);

    if (pcharValue == NULL)
    {
        return 0;
    }

    quint64 value = 0;
    //将字符数组强制转为long
    value = *((quint64*)pcharValue);
    return value;
}

/**
 * @brief CConverter::byteToBinary
 * 字节数组转二进制数组，使用int类型的数组来存放二进制数据
 * @param byteArr 字节数组
 * @param binary 存放二进制数据的int型数组
 */
void CConverter::byteToBinary(QByteArray byteArr, int* binary)
{
    int index = 0;
    for (int i = 0; i < byteArr.count(); i++)
    {
        int byte = byteArr[i];
        int bit_8 = (byte >> 7) & 0x01;
        int bit_7 = (byte >> 6) & 0x01;
        int bit_6 = (byte >> 5) & 0x01;
        int bit_5 = (byte >> 4) & 0x01;
        int bit_4 = (byte >> 3) & 0x01;
        int bit_3 = (byte >> 2) & 0x01;
        int bit_2 = (byte >> 1) & 0x01;
        int bit_1 = byte & 0x01;
        binary[index++] = bit_1;
        binary[index++] = bit_2;
        binary[index++] = bit_3;
        binary[index++] = bit_4;
        binary[index++] = bit_5;
        binary[index++] = bit_6;
        binary[index++] = bit_7;
        binary[index++] = bit_8;
    }
}

QString CConverter::charToTime(char *data)
{
    uchar Time0 = data[0];
    float fmsD0_D3 = (Time0 & 0xf) * 0.1f;
    float fmsD4_D7 = (Time0 & 0xf0) * 1.0f;

    uchar Time1 = data[1];
    int imsD0_D3 = (Time1 & 0xf) * 10;
    int imsD4_D7 = (Time1 & 0xf0) * 100;

    uchar Time2 = data[2];
    int isD0_D3 = (Time2 & 0xf) * 1;
    int isD4_D7 = (Time2 & 0xf0) * 10;

    uchar Time3 = data[3];
    int imD0_D3 = (Time3 & 0xf) * 1;
    int imD4_D7 = (Time3 & 0xf0) * 10;

    uchar Time4 = data[4];
    int ihD0_D3 = (Time4 & 0xf) *1;
    int ihD4_D5 = (Time4 & 0x30) * 10;
    int idD6_D7 = (Time4 & 0xc0) * 1;

    uchar Time5 = data[5];
    int idD0_D1 = (Time5 & 0x3) * 1;
    int idD2_D5 = (Time5 & 0x3c) * 100;

    QString qsMillisecond = QString::number(fmsD0_D3 + fmsD4_D7 + imsD0_D3 + imsD4_D7);
    QString qsSecond = QString::number(isD0_D3 + isD4_D7);
    QString qsMinute = QString::number(imD0_D3 + imD4_D7);
    QString qsHour = QString::number(ihD0_D3 + ihD4_D5);
    QString qsDay = QString::number(idD6_D7 + idD0_D1 + idD2_D5);

    qsDay+=qsHour;
    qsDay+=qsMinute;
    qsDay+=qsSecond;
    qsDay+=qsMillisecond;

    return QString(qsDay);
}

void CConverter::uintToIP(const unsigned int ip,char *stringIP)
{
     unsigned int tempIP=ip;

     for(int i=0;i<3;i++)
     {
        unsigned char part=(char)tempIP;

        char temp[4];

        sprintf(temp,"%d.",part);

        strcat(stringIP,temp);

        tempIP=tempIP>>8;
     }

     unsigned char part=(char)tempIP;

     char temp[4];

     sprintf(temp,"%d",part);

     strcat(stringIP,temp);
}

QByteArray CConverter::int8ToByte(int8_t target)
{
    int8_t iValue = target;
    int sizeOfInt = CConstants::SIZE_OF_INT8;
    char* btiValue = new char[sizeOfInt];

    //从iValue中拷贝4个字节到btiValue字符数组中
    memcpy(btiValue, (char*)&iValue, sizeOfInt);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btiValue的两倍
    QByteArray ret(btiValue, sizeOfInt);

    delete[] btiValue;
    return ret;
}

QByteArray CConverter::uint8ToByte(uint8_t target)
{
    uint8_t iValue = target;
    int sizeOfInt = CConstants::SIZE_OF_INT8;
    char* btiValue = new char[sizeOfInt];

    //从iValue中拷贝4个字节到btiValue字符数组中
    memcpy(btiValue, (char*)&iValue, sizeOfInt);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btiValue的两倍
    QByteArray ret(btiValue, sizeOfInt);

    delete[] btiValue;
    return ret;
}

/**
 * @brief Converter::intToByte
 * 整型转字节数组
 * @param target 需转的int数据
 * @return 字节数组
 */
QByteArray CConverter::intToByte(int target)
{
    int iValue = target;
    int sizeOfInt = CConstants::SIZE_OF_INT;
    char* btiValue = new char[sizeOfInt];

    //从iValue中拷贝4个字节到btiValue字符数组中
    memcpy(btiValue, (char*)&iValue, sizeOfInt);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btiValue的两倍
    QByteArray ret(btiValue, sizeOfInt);

    delete[] btiValue;
    return ret;
}

/**
 * @brief uintToByte
 * 无符号整型转字节数组
 * @param target 需转的无符号int数据
 * @return 字节数组
 */
QByteArray CConverter::uintToByte(uint target)
{
    uint iValue = target;
    int sizeOfInt = CConstants::SIZE_OF_INT;
    char* btiValue = new char[sizeOfInt];

    //从iValue中拷贝4个字节到btiValue字符数组中
    memcpy(btiValue, (char*)&iValue, sizeOfInt);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btiValue的两倍
    QByteArray ret(btiValue, sizeOfInt);

    delete[] btiValue;
    return ret;
}

/**
 * @brief Converter::doubleToByte
 * double转字节数组
 * @param target 需转数据
 * @return 字节数组
 */
QByteArray CConverter::doubleToByte(double target)
{
    double dValue = target;
    int sizeOfDouble = CConstants::SIZE_OF_DOUBLE;
    char* btdValue = new char[sizeOfDouble];

    memcpy(btdValue, (char*)&dValue, sizeOfDouble);

    QByteArray ret(btdValue, sizeOfDouble);

    delete[] btdValue;
    return ret;
}

/**
 * @brief Converter::floatToByte
 * float转字节数组
 * @param target 需转数据
 * @return 字节数组
 */
QByteArray CConverter::floatToByte(float target)
{
    float fValue = target;
    int sizeOfFloat = CConstants::SIZE_OF_FLOAT;
    char* btfValue = new char[sizeOfFloat];

    //从fValue中拷贝4个字节到btfValue字符数组中
    memcpy(btfValue, (char*)&fValue, sizeOfFloat);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btfValue的两倍
    QByteArray ret(btfValue, sizeOfFloat);

    delete[] btfValue;
    return ret;
}

/**
 * @brief shortToByte
 * ushort转字节数组
 * @param target 需转的short型数据
 * @return 表示该数据的字节数组
 */
QByteArray CConverter::ushortToByte(ushort target)
{
    ushort sValue = target;
    int sizeOfShort = CConstants::SIZE_OF_SHORT;
    char* btsValue = new char[sizeOfShort];

    //从fValue中拷贝4个字节到btfValue字符数组中
    memcpy(btsValue, (char*)&sValue, sizeOfShort);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btsValue的两倍
    QByteArray ret(btsValue, sizeOfShort);

    delete[] btsValue;
    return ret;
}

/**
 * @brief CConverter::shortToByte
 * 有符号short转字节数组
 * @param target
 * @return
 */
QByteArray CConverter::shortToByte(short target)
{
    short sValue = target;
    int sizeOfShort = CConstants::SIZE_OF_SHORT;
    char* btsValue = new char[sizeOfShort];

    //从fValue中拷贝4个字节到btfValue字符数组中
    memcpy(btsValue, (char*)&sValue, sizeOfShort);

    //使用字符数组创建QByteArray对象，这里一定要加上长度，
    //否则在创建该对象时长度会为btsValue的两倍
    QByteArray ret(btsValue, sizeOfShort);

    delete[] btsValue;
    return ret;
}

/**
 * @brief charToByte
 * char转字节数组
 * @param target
 * @return
 */
QByteArray CConverter::charToByte(char target)
{
    //直接将char填入字节数组中，返回
    QByteArray ret;
    ret.append(target);
    return ret;
}

/**
 * @brief CConverter::ucharToByte
 * uchar转字节数组
 * @param target
 * @return
 */
QByteArray CConverter::ucharToByte(uchar target)
{
    //直接将char填入字节数组中，返回
    QByteArray ret;
    ret.append(target);
    return ret;
}

/**
 * @brief stringToByte
 * 字符串转字节数组
 * @param target 字符串
 * @return 字节数组
 */
QByteArray CConverter::stringToByte(QString target)
{
    return target.toUtf8();
}

/**
 * @brief CConverter::longToByte
 * 长整型转字节数组
 * @param target 长整型数据
 * @return
 */
QByteArray CConverter::qint64ToByte(qint64 target)
{
    qint64 value = target;
    int sizeOfLong = CConstants::SIZE_OF_QINT64;
    char* btlValue = new char[sizeOfLong];

    memcpy(btlValue, (char*)&value, sizeOfLong);

    QByteArray ret(btlValue, sizeOfLong);

    delete[] btlValue;
    return ret;
}

/**
 * @brief CConverter::uint64ToByte
 * 无符号长整型转字节数组
 * @param target
 * @return
 */
QByteArray CConverter::quint64ToByte(quint64 target)
{
    quint64 value = target;
    int sizeOfLong = CConstants::SIZE_OF_QINT64;
    char* btlValue = new char[sizeOfLong];

    memcpy(btlValue, (char*)&value, sizeOfLong);

    QByteArray ret(btlValue, sizeOfLong);

    delete[] btlValue;
    return ret;
}

/**
 * @brief CConverter::binaryToByte
 * 将二进制数组转成字节数组
 * @param binary 二进制数组
 * @param length 二进制数组长度
 * @return
 */
QByteArray CConverter::binaryToByte(int* binary, int length)
{
    //每个字节占8位。使用binary的长度除以8获取字节长度
    int byteLength = (int)(length / 8);

    QByteArray ret(byteLength, 0);

    //循环将二进制数据转成字节存入字节数组中
    int index = 0;
    for (int i = 0; i < byteLength; i++)
    {
        int byte = 0;
        byte = binary[index];
        index++;
        byte = byte | binary[index] << 1;
        index++;
        byte = byte | binary[index] << 2;
        index++;
        byte = byte | binary[index] << 3;
        index++;
        byte = byte | binary[index] << 4;
        index++;
        byte = byte | binary[index] << 5;
        index++;
        byte = byte | binary[index] << 6;
        index++;
        byte = byte | binary[index] << 7;
        index++;
        ret[i] = byte;
    }

    return ret;
}

QByteArray CConverter::bitArrayToBytes(const QBitArray &bitArr)
{
    if( 0 != (bitArr.size() % 8) ) return QByteArray();

    QByteArray tmp;
    tmp.resize(bitArr.size()/8);

    char *data = tmp.data();
    memset(data, 0, tmp.length());

    char ctmp = 0x01;
    char ccal = 0x00;
    for(int i=0; i<bitArr.size(); ++i)
    {
        if( bitArr.testBit(i) )
        {
            ctmp <<= (8-((i+1)%8));
            ccal |= ctmp;
        }

        if( 0 == ((i+1)%8) )
        {
            *data |= ccal;
            ++data;

            ctmp = 0x01;
            ccal = 0x00;
        }
    }

    return tmp;
}

char CConverter::complementToChar(char sourData)
{
    char tmpData = sourData;
    char retData = ((tmpData&(0x80))|(~sourData)) + 1;
    return retData;
}

char CConverter::charToComplement(char sourData)
{
    char tmpData = sourData;
    char retData = ((tmpData&(0x80))|(~sourData)) + 1;
    return retData;
}

/**
 * @brief CConverter::bitArrayToInt
 * 将bit数组转成int类型数据
 * @param bitArr 需转为int的bit数组
 * @param length bit数组长度
 * @return
 */
int CConverter::bitArrayToInt(int bitArr[], int length)
{
    int ret = 0;
    for (int i = 0; i < length; i++)
    {
        ret |= bitArr[i] << i;
    }

    return ret;
}

/**
 * @brief CConverter::intToBitArray
 * 将int型数值转成bit数组,需在外面分配bit数组空间
 * @param value 需转的值
 * @param length bitArr数组长度
 * @param bitArr 返回回的bit数组
 */
void CConverter::intToBitArray(int value, int length, int* bitArr)
{
    for (int i = 0; i < length; i++)
    {
        bitArr[i] = value >> i & 0x01;
    }
}

/**
 * @brief CConverter::byteToPChar
 * 将字节数组转为char型指针
 * @param byteArr 字节数组
 * @param length 长度
 * @return 字节数组大于指定长度，返回NULL，否则返回指定长度的字节数组char型指针
 */
char* CConverter::byteToPChar(QByteArray& byteArr, int length)
{
    int size = byteArr.size();

    //判断字节数组长度是否大于指定长度，大于直接返回NULL
    if (size > length)
    {
        return NULL;
    }

    //不够长度，在后面添0
    if (size < length)
    {
        byteArr.append(QByteArray(length - byteArr.size(), 0));
    }

    char* pcharValue;
    pcharValue = byteArr.data();

    return pcharValue;
}

// QByteArray转16进制字符串//add
QString CConverter::byteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length() / 2;

    for (int i = 1; i < len; i++)
    {
        ret.insert(2 * i + i - 1, " ");
    }

    return ret;
}

QByteArray CConverter::hexToByteArray(QString data)
{
    bool ok;
    QByteArray ret;
    data = data.trimmed();
    data = data.simplified();
    QStringList sl = data.split(" ");
    foreach (QString s, sl)
    {
        if (!s.isEmpty())
        {
            char c = s.toInt(&ok, 16) & 0xFF;
            if (ok)
            {
                ret.append(c);
            }
            else
            {
            }
        }
    }
    return ret;
}

//十位数转BCD码QByteArray//add
short CConverter::tenDigitNumberToBCD(short tensNumber)
{
    short validNumber = tensNumber % 100;
    short singleDigit = validNumber % 10;
    short tensDigit = validNumber / 10;
    //    QByteArray bcdByte;
    //    bcdByte.resize(1);
    //    bcdByte[0] = (singleDigit & 0x0000000f) | ((tensDigit & 0x0000000f)<<4) ;
    return (singleDigit & 0x0000000f) | ((tensDigit & 0x0000000f) << 4);
}

// QByteArray内部字节反转
QByteArray CConverter::qByteArrayReverse(QByteArray message, int byteNumber)
{
    QByteArray newValue;
    newValue.resize(byteNumber);
    for (int i = 0; i < byteNumber; i++)
    {
        short temp = message[byteNumber - i - 1];
        newValue[i] = temp;
    }
    return newValue;
}

bool CConverter::hexToShort(const char* data, short &value)
{
    if( strlen(data) != 4 ) return false;

    for(int i=0; i<4; ++i)
    {
        char c = data[i];

        if( (c >= 'a' && c <= 'f') ) continue;
        if( (c >= 'A' && c <= 'F') ) continue;
        if( (c >= '0' && c <= '9') ) continue;
        else return false;
    }

    sscanf(data,"%4X",&value);

    return true;
}

QString CConverter::ushortToHexString(ushort src, bool bHighLow)
{
    char *pData = (char*)&src;

    QByteArray tmp;

    if( bHighLow )
    {   //实际存储顺序与显示顺序不一致，需要调换
        char data[3] = {0};

        data[0] = pData[1];
        data[1] = pData[0];
        tmp.append(data, sizeof(ushort));
    }
    else tmp.append(pData, sizeof(ushort));

    QString ret(tmp.toHex().toUpper());
    return ret;
}
