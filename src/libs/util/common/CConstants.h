/*
 *　Copyright (c)　2015,成都能通科技有限公司
 *　All rights reserved.
 *
 *　文件名称：cconstants.h
 *　文件标识：见配置管理计划书
 *　摘要：该文件对CConstants类的和相应的成员及方法进行了定义。
 *       CConstants类为常量类，定义了系统中需要使用到的常量。
 */

#ifndef CCONSTANTS_H
#define CCONSTANTS_H

#include "util_global.h"
#include <QString>

class UTILSHARED_SELF_EXPORT CConstants
{
public:
    CConstants();

    static const double DOUBLE_TOLERANCE;
    static const float FLOAT_TOLERANCE;

    /**
     * @brief SIZE_OF_INT
     * int型所占字节数
     */
    static const int SIZE_OF_INT;
    /**
     * @brief SIZE_OF_FLOAT
     * float型所占字节数
     */
    static const int SIZE_OF_FLOAT;
    /**
     * @brief SIZE_OF_DOUBLE
     * double型所占字节数
     */
    static const int SIZE_OF_DOUBLE;

    /**
     * @brief SIZE_OF_INT8
     * short型所占字节数
     */
    static const int SIZE_OF_INT8;

    /**
     * @brief SIZE_OF_SHORT
     * short型所占字节数
     */
    static const int SIZE_OF_SHORT;

    /**
     * @brief SIZE_OF_QINT64
     * qint64型所占字节数
     */
    static const int SIZE_OF_QINT64;

    /**
     * @brief STR_INT
     * int
     */
    static const QString STR_INT;

    /**
     * @brief STR_UINT
     * uint
     */
    static const QString STR_UINT;

    /**
     * @brief STR_FLOAT
     * float
     */
    static const QString STR_FLOAT;

    /**
     * @brief STR_DOUBLE
     * double
     */
    static const QString STR_DOUBLE;

    /**
     * @brief STR_BYTEARRAY
     * bytearray
     */
    static const QString STR_BYTEARRAY;

    /**
     * @brief STR_LIST
     * list
     */
    static const QString STR_LIST;

    /**
     * @brief STR_STRING
     * string
     */
    static const QString STR_STRING;

    /**
     * @brief STR_CHAR
     * char
     */
    static const QString STR_CHAR;

    /**
     * @brief STR_UCHAR
     * uchar
     */
    static const QString STR_UCHAR;

    /**
     * @brief STR_SHORT
     * ushort
     */
    static const QString STR_USHORT;

    /**
     * @brief STR_SHORT
     * 有符号short型
     */
    static const QString STR_SHORT;

    /**
     * @brief STR_QINT64
     * qint64
     */
    static const QString STR_QINT64;

    /**
     * @brief STR_QUINT64
     * quint64
     */
    static const QString STR_QUINT64;
};

#endif  // CCONSTANTS_H
