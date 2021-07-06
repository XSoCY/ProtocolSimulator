#ifndef HEXLINEEDIT_H
#define HEXLINEEDIT_H

#include <QDomElement>
#include <QLineEdit>

/**
 * @brief The HexLineEdit class

<Widget paramID="102" type="HexLineEdit" inputProperty="paramVaule" label="任务标识" len="4"/>

 */

class HexLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit HexLineEdit(const QDomElement& doc_element, QWidget* parent = nullptr);

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
    quint16 convSPolyToSaveData(quint16 show_data) const;
    quint16 convSPolyToShowData(quint16 save_data) const;

private:
    int len_ = 0;
    bool encryption_ = false;
};

#endif  // HEXLINEEDIT_H
