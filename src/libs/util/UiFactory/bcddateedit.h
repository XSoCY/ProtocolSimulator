#ifndef BCDDATESETTING_H
#define BCDDATESETTING_H
#include <QDateEdit>
#include <QDomElement>

class BcdDateEdit : public QDateEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit BcdDateEdit(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(const bool editmode);

protected:
    uchar bcdTime2DecimalUChar(uchar bcd);
    char  decimal2BcdUChar(int firstHalf, int secondHalf) const;
};

#endif  // BCDDATESETTING_H
