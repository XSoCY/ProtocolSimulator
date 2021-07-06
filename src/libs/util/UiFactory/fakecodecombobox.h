#ifndef FAKECODECOMBOBOX_H
#define FAKECODECOMBOBOX_H

#include <QComboBox>
#include <QDomElement>

class FakeCodeComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant fakeDesc READ fakeCodeDesc WRITE setFakeCodeDesc)
    Q_PROPERTY(QVariant fakeCode READ fakeCode WRITE setFakeCode)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit FakeCodeComboBox(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant fakeCodeDesc() const;
    void     setFakeCodeDesc(const QVariant& param_vaule);

    QVariant fakeCode() const;
    void     setFakeCode(const QVariant& param_vaule);

    bool editMode() const;
    void setEditMode(bool edit_mode);

    bool eventFilter(QObject *obj, QEvent *event);

private:
    bool edit_mode_ = false;

    quint64 cur_fake_code_desc_ = 0;
    quint8 cur_fake_code_ = 1;
};

#endif // FAKECODECOMBOBOX_H
