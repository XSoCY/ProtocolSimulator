#include "worker.h"
#include <QTimer>

Worker::Worker(QObject *parent)
    : QObject(parent)
    , m_timer(nullptr)
{

}

Worker::~Worker()
{
    m_timer->deleteLater();
}

void Worker::startAutoSend(int interval)
{
    if( m_timer == nullptr) {
        m_timer = new QTimer;
        connect(m_timer, &QTimer::timeout, this, &Worker::onTimeOut);
    }
    m_timer->start(interval);
}

void Worker::stopAutoSend()
{
    m_timer->stop();
}

/*void Worker::setSendContent(const QByteArray content)
{
    m_sendContent = content;
}*/

void Worker::onTimeOut()
{
    emit sendData();
}
