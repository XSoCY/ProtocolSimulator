#include "bcddateedit.h"
#include <QDebug>
BcdDateEdit::BcdDateEdit(const QDomElement& doc_element, QWidget* parent) : QDateEdit(parent)
{
    Q_UNUSED(doc_element);
}

QVariant BcdDateEdit::paramVaule() const
{
    QVariant   var;
    QByteArray resultArray;
    QDate      date        = this->date();
    int        yearHead    = date.year() / 100;
    int        yearTail    = date.year() % 100;
    int        month       = date.month();
    int        day         = date.day();
    char       bcdYearHead = decimal2BcdUChar(yearHead / 10, yearHead % 10);
    char       bcdYearTail = decimal2BcdUChar(yearTail / 10, yearTail % 10);
    char       bcdMonth    = decimal2BcdUChar(month / 10, month % 10);
    char       bcdDay      = decimal2BcdUChar(day / 10, day % 10);
    resultArray.append(bcdYearHead);
    resultArray.append(bcdYearTail);
    resultArray.append(bcdMonth);
    resultArray.append(bcdDay);
    var.setValue(resultArray);
    return var;
}

char BcdDateEdit::decimal2BcdUChar(int firstHalf, int secondHalf) const
{
    char bcdUChar = static_cast<char>((firstHalf << 4) + secondHalf);
    return bcdUChar;
}

uchar BcdDateEdit::bcdTime2DecimalUChar(uchar bcd)
{
    uchar decimal;
    decimal = bcd >> 4;
    return (decimal = decimal * 10 + (bcd &= 0x0F));
}
void BcdDateEdit::setParamVaule(const QVariant& param_vaule)
{
    if (param_vaule.canConvert<QByteArray>()) {
        QByteArray bcdArray = param_vaule.toByteArray();
        if (bcdArray.length() != 4)
            return;
        uchar yearHeadUChar = bcdTime2DecimalUChar(static_cast<uchar>(bcdArray.at(0)));
        uchar yearTailUChar = bcdTime2DecimalUChar(static_cast<uchar>(bcdArray.at(1)));
        uchar monthUChar    = bcdTime2DecimalUChar(static_cast<uchar>(bcdArray.at(2)));
        uchar dayUChar      = bcdTime2DecimalUChar(static_cast<uchar>(bcdArray.at(3)));

        bool ok    = true;
        int  year  = QString("%1%2").arg(yearHeadUChar).arg(yearTailUChar).toInt(&ok);
        int  month = static_cast<int>(monthUChar);
        int  day   = static_cast<int>(dayUChar);
        if (ok) {
            setDate(QDate(year, month, day));
        }
    }
}

bool BcdDateEdit::editMode() const
{
    return !isReadOnly();
}

void BcdDateEdit::setEditMode(const bool editmode)
{
    setReadOnly(!editmode);
}
