#include "t0timesetting.h"
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QSpinBox>

T0TimeSetting::T0TimeSetting(const QDomElement& doc_element, QWidget* parent) : QWidget(parent)
{
    auto h_layout = new QHBoxLayout;
    setLayout(h_layout);

    h_layout->addWidget(day_ = new QSpinBox);
    h_layout->addWidget(hour_ = new QSpinBox);
    h_layout->addWidget(min_ = new QSpinBox);
    h_layout->addWidget(second_ = new QDoubleSpinBox);

    day_->setSuffix("天");
    day_->setRange(0, 366);
    hour_->setSuffix("时");
    hour_->setRange(0, 23);
    min_->setSuffix("分");
    min_->setRange(0, 59);
    second_->setSuffix("秒");
    second_->setRange(0, 59.9999);
    second_->setDecimals(4);
}

QVariant T0TimeSetting::paramVaule() const
{
    auto second_value = second_->value();
    auto min_value    = min_->value();
    auto hour_value   = hour_->value();
    auto day_value    = day_->value();

    auto ms_0_1  = static_cast<quint64>(second_value * 10000) % 10;
    auto ms_1    = static_cast<quint64>(second_value * 1000) % 10;
    auto ms_10   = static_cast<quint64>(second_value * 100) % 10;
    auto ms_100  = static_cast<quint64>(second_value * 10) % 10;
    auto s_1     = static_cast<quint64>(second_value) % 10;
    auto s_10    = static_cast<quint64>(second_value / 10) % 10;
    auto min_1   = static_cast<quint64>(min_value % 10);
    auto min_10  = static_cast<quint64>((min_value / 10) % 10);
    auto hour_1  = static_cast<quint64>(hour_value % 10);
    auto hour_10 = static_cast<quint64>((hour_value / 10) % 10);
    auto day_1   = static_cast<quint64>(day_value % 10);
    auto day_10  = static_cast<quint64>((day_value / 10) % 10);
    auto day_100 = static_cast<quint64>((day_value / 100) % 10);

    quint64 value = 0;

    value = value | (ms_0_1 << 0);
    value = value | (ms_1 << 4);
    value = value | (ms_10 << 8);
    value = value | (ms_100 << 12);
    value = value | (s_1 << 16);
    value = value | (s_10 << 20);
    value = value | (min_1 << 24);
    value = value | (min_10 << 28);
    value = value | (hour_1 << 32);
    value = value | (hour_10 << 36);
    value = value | (day_1 << 38);
    value = value | (day_10 << 42);
    value = value | (day_100 << 46);

    return value;
}

void T0TimeSetting::setParamVaule(const QVariant& param_vaule)
{
    if (!param_vaule.canConvert<quint64>()) {
        return;
    }
    auto value = param_vaule.toULongLong();

    auto ms_0_1  = (value >> 0) & ((1 << 4) - 1);
    auto ms_1    = (value >> 4) & ((1 << 4) - 1);
    auto ms_10   = (value >> 8) & ((1 << 4) - 1);
    auto ms_100  = (value >> 12) & ((1 << 4) - 1);
    auto s_1     = (value >> 16) & ((1 << 4) - 1);
    auto s_10    = (value >> 20) & ((1 << 4) - 1);
    auto min_1   = (value >> 24) & ((1 << 4) - 1);
    auto min_10  = (value >> 28) & ((1 << 4) - 1);
    auto hour_1  = (value >> 32) & ((1 << 4) - 1);
    auto hour_10 = (value >> 36) & ((1 << 2) - 1);
    auto day_1   = (value >> 38) & ((1 << 4) - 1);
    auto day_10  = (value >> 42) & ((1 << 4) - 1);
    auto day_100 = (value >> 46) & ((1 << 2) - 1);

    second_->setValue(s_10 * 10.0 + s_1 + ms_100 * 0.1 + ms_10 * 0.01 + ms_1 * 0.001 + ms_0_1 * 0.0001);

    min_->setValue(static_cast<int>((min_10 * 10 + min_1 * 1)));
    hour_->setValue(static_cast<int>((hour_10 * 10 + hour_1 * 1)));
    day_->setValue(static_cast<int>((day_100 * 100 + day_10 * 10 + day_1 * 1)));
}

bool T0TimeSetting::editMode() const
{
    return edit_mode_;
}

void T0TimeSetting::setEditMode(const bool editmode)
{
    edit_mode_ = editmode;

    second_->setReadOnly(!editmode);
    min_->setReadOnly(!editmode);
    hour_->setReadOnly(!editmode);
    day_->setReadOnly(!editmode);
}
