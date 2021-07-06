#ifndef STRINGLINEEDIT_H
#define STRINGLINEEDIT_H

#include <QDebug>
#include <QDomElement>
#include <QLineEdit>
/**
 * @brief The StringLineEdit class

<Widget paramID="101" type="StringLineEdit" inputProperty="paramVaule" label="任务代号（保留）"
len="20"/>

 */

class StringLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit StringLineEdit(const QDomElement &doc_element, QWidget *parent = nullptr);

    QVariant paramVaule() const;
    void setParamVaule(const QVariant &param_vaule);

    bool editMode() const
    {
        return !isReadOnly();
    }
    void setEditMode(const bool editmode)
    {
        setReadOnly(!editmode);
    }

private:
    int len_        = 0;
    QString encode_ = "UTF-8";
};

#endif  // STRINGLINEEDIT_H
