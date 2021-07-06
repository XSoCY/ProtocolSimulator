#ifndef STRING2NUM_H
#define STRING2NUM_H

#include <QtCore>

//字符串转数值(支持0x开始的字符串)
#define STRING2UINT8(str) (quint8) QString(str).trimmed().toULongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT16(str) (quint16) QString(str).trimmed().toULongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT32(str) (quint32) QString(str).trimmed().toULongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT64(str) (quint64) QString(str).trimmed().toULongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT8(str) (qint8) QString(str).trimmed().toLongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT16(str) (qint16) QString(str).trimmed().toLongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT32(str) (qint32) QString(str).trimmed().toLongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT64(str) (qint64) QString(str).trimmed().toLongLong(0, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)

//带结果检测的字符串转数值(支持0x开始的字符串)
#define STRING2UINT8_CHECK(str, ok) (quint8) QString(str).trimmed().toULongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT16_CHECK(str, ok) (quint16) QString(str).trimmed().toULongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT32_CHECK(str, ok) (quint32) QString(str).trimmed().toULongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2UINT64_CHECK(str, ok) (quint64) QString(str).trimmed().toULongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT8_CHECK(str, ok) (qint8) QString(str).trimmed().toLongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT16_CHECK(str, ok) (qint16) QString(str).trimmed().toLongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT32_CHECK(str, ok) (qint32) QString(str).trimmed().toLongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)
#define STRING2INT64_CHECK(str, ok) (qint64) QString(str).trimmed().toLongLong(ok, QString(str).startsWith("0x", Qt::CaseInsensitive) ? 16 : 10)

#define SplicingTwoInt(value1,value2) (QString::number(value1) + QString::number(value2)).toInt()

#endif // STRING2NUM_H
