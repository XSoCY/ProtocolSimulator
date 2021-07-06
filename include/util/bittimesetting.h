#ifndef BITTIMESETTINGWITHYEAR_H
#define BITTIMESETTINGWITHYEAR_H

#include <QDateTimeEdit>
#include <QDomElement>
#include <QWidget>

class BitTimeSetting : public QDateTimeEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit BitTimeSetting(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

private:
    int mirco_second_start_bit_ = 0;
    int mirco_second_bit_len_   = 0;
    int second_start_bit_       = 0;
    int second_bit_len_         = 0;
    int minute_start_bit_       = 0;
    int minute_bit_len_         = 0;
    int hour_start_bit_         = 0;
    int hour_bit_len_           = 0;
    int day_start_bit_          = 0;
    int day_bit_len_            = 0;
    int year_start_bit_         = 0;
    int year_bit_len_           = 0;
    int valid_start_bit_        = 0;

    bool has_mirco_second_ = false;
    bool has_year_         = false;
};

#endif  // BITTIMESETTINGWITHYEAR_H
