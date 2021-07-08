#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class QTimer;
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void sendData();

public slots:
    void startAutoSend(int interval);
    void stopAutoSend();
    //void setSendContent(const QByteArray content);

private slots:
    void onTimeOut();

private:
    QTimer *m_timer;
    //QByteArray m_sendContent;
};

#endif // WORKER_H
