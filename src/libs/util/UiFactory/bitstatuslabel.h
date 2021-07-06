#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QDomElement>
#include <QLabel>
#include <QTimer>
#include <QVariant>

/**
 * @brief The BitStatusLabel class

<Widget paramID="3" type="BitStatusLabel" inputProperty="paramVaule" label="调制器状态" bitStart="0" normalValue="1"/>
<Widget paramID="3" type="BitStatusLabel" inputProperty="paramVaule" label="解调器状态" bitStart="1" normalValue="1"/>
<Widget paramID="3" type="BitStatusLabel" inputProperty="paramVaule" label="时频板状态" bitStart="2" normalValue="1"/>
<Widget paramID="3" type="BitStatusLabel" inputProperty="paramVaule" label="安控基带软件状态" bitStart="3" normalValue="1"/>
<Widget paramID="3" type="BitStatusLabel" inputProperty="paramVaule" label="切换板状态" bitStart="4" normalValue="1"/>

 */

class StatusAttemper;
class StatusTimer;

class StatusTimer : public QTimer
{
public:
    explicit StatusTimer(StatusAttemper* attemper, QObject* parent = Q_NULLPTR);

protected:
    void timerEvent(QTimerEvent*) override;

private:
    StatusAttemper* m_attemper = nullptr;
};

class StatusAttemper
{
    Q_DISABLE_COPY(StatusAttemper)
public:
    enum DeviceStatus
    {
        Normal,
        Abnormal,
        Unknown
    };
    explicit StatusAttemper();
    virtual ~StatusAttemper();
    DeviceStatus status() const;
    void         setStatus(DeviceStatus status);

protected:
    virtual void setLabelIcon(const DeviceStatus status) = 0;

private:
    DeviceStatus m_status  = Unknown;
    StatusTimer* m_timer   = nullptr;
    int          m_timeout = 5000;
};

class StatusLabel : public QLabel, public StatusAttemper
{
    Q_OBJECT
public:
    explicit StatusLabel(QWidget* parent = nullptr);
    virtual ~StatusLabel();

protected:
    virtual void setLabelIcon(const DeviceStatus status);

private:
    void initPixmap();

private:
    QPixmap red_;
    QPixmap green_;
    QPixmap gray_;
};

class BitStatusLabel : public StatusLabel
{
    Q_OBJECT
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit BitStatusLabel(const QDomElement& doc_element, QWidget* parent = nullptr);

    QVariant paramVaule() const;
    void     setParamVaule(const QVariant& param_vaule);

    bool editMode() const
    {
        return false;
    }

    void setEditMode(const bool editmode) {}

private:
    int bit_start_    = 0;
    int normal_value_ = 1;
};

#endif  // STATUSLABEL_H
