#include "bitstatuslabel.h"
#include <QDebug>
#include <QPainter>

StatusLabel::StatusLabel(QWidget *parent) : QLabel(parent), StatusAttemper()
{
    initPixmap();
    setPixmap(gray_);
}

StatusLabel::~StatusLabel() {}

void StatusLabel::setLabelIcon(const DeviceStatus status)
{
    if (status == Normal) {
        setPixmap(green_);
        setToolTip("正常");
    }
    else if (status == Abnormal) {
        setPixmap(red_);
        setToolTip("异常");
    }
    else {
        setPixmap(gray_);
        setToolTip("未知");
    }
}

void StatusLabel::initPixmap()
{
    //    green_ = QPixmap(20, 20);
    //    green_.fill(Qt::transparent);
    //    {
    //        QPainter painter(&green_);
    //        painter.setRenderHint(QPainter::Antialiasing);
    //        painter.setPen(Qt::NoPen);
    //        painter.setBrush(Qt::green);
    //        painter.drawEllipse(0, 0, green_.width(), green_.height());
    //    }

    //    red_ = QPixmap(20, 20);
    //    red_.fill(Qt::transparent);
    //    {
    //        QPainter painter(&red_);
    //        painter.setRenderHint(QPainter::Antialiasing);
    //        painter.setPen(Qt::NoPen);
    //        painter.setBrush(Qt::red);
    //        painter.drawEllipse(0, 0, red_.width(), red_.height());
    //    }

    //    gray_ = QPixmap(20, 20);
    //    gray_.fill(Qt::transparent);
    //    {
    //        QPainter painter(&gray_);
    //        painter.setRenderHint(QPainter::Antialiasing);
    //        painter.setPen(Qt::NoPen);
    //        painter.setBrush(Qt::gray);
    //        painter.drawEllipse(0, 0, gray_.width(), gray_.height());
    //    }

    green_ = QPixmap(20, 20);
    green_.fill(Qt::transparent);
    {
        green_.load(":icon/res/green.png");
    }

    red_ = QPixmap(20, 20);
    red_.fill(Qt::transparent);
    {
        red_.load(":icon/res/red.png");
    }

    gray_ = QPixmap(20, 20);
    gray_.fill(Qt::transparent);
    {
        gray_.load(":icon/res/gray.png");
    }
}

StatusAttemper::StatusAttemper() : m_status(Unknown)
{
    m_timer = new StatusTimer(this);
}

StatusAttemper::~StatusAttemper()
{
    if (m_timer) {
        delete m_timer;
        m_timer = nullptr;
    }
}

StatusAttemper::DeviceStatus StatusAttemper::status() const
{
    return m_status;
}

void StatusAttemper::setStatus(DeviceStatus status)
{
    m_status = status;
    setLabelIcon(status);

    if (status != Unknown) {
        m_timer->start(m_timeout);
    }
}

void StatusAttemper::setLabelIcon(const DeviceStatus status) {}

StatusTimer::StatusTimer(StatusAttemper *attemper, QObject *parent)
    : QTimer(parent), m_attemper(attemper)
{
    setSingleShot(true);
}

void StatusTimer::timerEvent(QTimerEvent *)
{
    if (m_attemper) {
        m_attemper->setStatus(StatusAttemper::Unknown);
    }
}

BitStatusLabel::BitStatusLabel(const QDomElement &doc_element, QWidget *parent)
    : StatusLabel(parent)
{
    bit_start_    = doc_element.attribute("bitStart", "0").toInt();
    normal_value_ = doc_element.attribute("normalValue", "1").toInt();
}

QVariant BitStatusLabel::paramVaule() const
{
    return QVariant();
}

void BitStatusLabel::setParamVaule(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<int>()) {
        auto int_value = param_vaule.toInt();
        if (((int_value >> bit_start_) & 1) ^ normal_value_) {
            //异常
            setStatus(StatusAttemper::Abnormal);
        }
        else {
            //正常
            setStatus(StatusAttemper::Normal);
        }
    }
}
