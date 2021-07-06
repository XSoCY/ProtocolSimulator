#ifndef TIMESTAMPDISPLAY_H
#define TIMESTAMPDISPLAY_H

#include <QDomElement>
#include <QLabel>
#include <QVariant>

/**
 * @brief The TimeStampDisplay class

<Widget paramID="101" type="TimeStampDisplay" inputProperty="paramVaule" label="时标" coefficient="0.1"/>

 */

class TimeStampDisplay : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit TimeStampDisplay(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return false;
    }
    void setEditMode(const bool editmode) {}

private:
    double coefficient_ = 0;
};

#endif // TIMESTAMPDISPLAY_H
