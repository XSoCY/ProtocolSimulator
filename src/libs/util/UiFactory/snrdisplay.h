#ifndef SNRDISPLAY_H
#define SNRDISPLAY_H

#include <QDomElement>
#include <QLabel>
#include <QVariant>

/**
 * @brief The SNRDisplay class

<Widget paramID="101" type="SNRDisplay" inputProperty="paramVaule" label="信噪比">
    <Signal startBit="32" len="32"/>
    <Noise startBit="0" len="32"/>
</Widget>

 */

class SNRDisplay : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit SNRDisplay(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return false;
    }
    void setEditMode(const bool editmode) {}

private:
    void init(const QDomElement& doc_element);

private:
    int signal_start_ = 0;
    int signal_len_ = 0;
    int noise_start_ = 0;
    int noise_len_ = 0;
};

#endif // SNRDISPLAY_H
