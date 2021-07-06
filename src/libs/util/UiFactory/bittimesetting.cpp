#include "bittimesetting.h"

BitTimeSetting::BitTimeSetting(const QDomElement& doc_element, QWidget* parent) : QDateTimeEdit(parent)
{
    setMinimumDate(QDate(2000, 1, 1));

    auto display_format = doc_element.attribute("displayFormat");
    setDisplayFormat(display_format);

    mirco_second_start_bit_ = doc_element.attribute("mirco_second_start_bit").toInt();
    mirco_second_bit_len_   = doc_element.attribute("mirco_second_bit_len").toInt();
    second_start_bit_       = doc_element.attribute("second_start_bit").toInt();
    second_bit_len_         = doc_element.attribute("second_bit_len").toInt();
    minute_start_bit_       = doc_element.attribute("minute_start_bit").toInt();
    minute_bit_len_         = doc_element.attribute("minute_bit_len").toInt();
    hour_start_bit_         = doc_element.attribute("hour_start_bit").toInt();
    hour_bit_len_           = doc_element.attribute("hour_bit_len").toInt();
    day_start_bit_          = doc_element.attribute("day_start_bit").toInt();
    day_bit_len_            = doc_element.attribute("day_bit_len").toInt();
    year_start_bit_         = doc_element.attribute("year_start_bit").toInt();
    year_bit_len_           = doc_element.attribute("year_bit_len").toInt();

    valid_start_bit_ = doc_element.attribute("valid_start_bit").toInt();

    has_year_         = doc_element.hasAttribute("year_start_bit");
    has_mirco_second_ = doc_element.hasAttribute("mirco_second_start_bit");
}

QVariant BitTimeSetting::paramVaule() const
{
    quint64 value = 0;

    auto date_time    = dateTime();
    auto mirco_second = quint64(date_time.time().msec());
    auto second       = quint64(date_time.time().second());
    auto minute       = quint64(date_time.time().minute());
    auto hour         = quint64(date_time.time().hour());
    auto day          = quint64(date_time.date().day());
    auto vaild        = quint64(1);
    auto year         = quint64(date_time.date().year() - 2000);

    if (has_mirco_second_) {
        value = value | (mirco_second << mirco_second_start_bit_);
    }
    value = value | (second << second_start_bit_);
    value = value | (minute << minute_start_bit_);
    value = value | (hour << hour_start_bit_);
    value = value | (day << day_start_bit_);
    value = value | (vaild << valid_start_bit_);
    if (has_year_) {
        value = value | (year << year_start_bit_);
    }

    return value;
}

void BitTimeSetting::setParamVaule(const QVariant& param_vaule)
{
    if (!param_vaule.canConvert<quint64>()) {
        return;
    }
    auto value = param_vaule.toULongLong();

    auto mirco_second = (value >> mirco_second_start_bit_) & ((1 << mirco_second_bit_len_) - 1);
    auto second       = (value >> second_start_bit_) & ((1 << second_bit_len_) - 1);
    auto minute       = (value >> minute_start_bit_) & ((1 << minute_bit_len_) - 1);
    auto hour         = (value >> hour_start_bit_) & ((1 << hour_bit_len_) - 1);
    auto day          = (value >> day_start_bit_) & ((1 << day_bit_len_) - 1);
    auto year         = (value >> year_start_bit_) & ((1 << year_bit_len_) - 1);
    year += 2000;

    QDate date = QDate(static_cast<int>(year), 1, 1);
    if (day != 0) {
        date = date.addDays(static_cast<int>(day - 1));
    }
    QDateTime time(date, QTime(static_cast<int>(hour), static_cast<int>(minute), static_cast<int>(second),
                               static_cast<int>(mirco_second)));
    setDateTime(time);
}

bool BitTimeSetting::editMode() const
{
    return !isReadOnly();
}

void BitTimeSetting::setEditMode(const bool editmode)
{
    setReadOnly(!editmode);
}
