#ifndef STANDARDTIMESETTING_H
#define STANDARDTIMESETTING_H

#include <QTimeEdit>
#include <QDomElement>
#include <QVariant>
#include <QTime>

class StandardTimeSetting: public QTimeEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit StandardTimeSetting(const QDomElement& doc_element, QWidget* parent = nullptr);
    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return !isReadOnly();
    }
    void setEditMode(const bool editmode)
    {
        setReadOnly(!editmode);
    }
private:
    double coefficient_ = 0;
};

#endif // STANDARDTIMESETTING_H
