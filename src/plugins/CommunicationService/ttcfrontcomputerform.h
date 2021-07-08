#ifndef TTCFRONTCOMPUTERFORM_H
#define TTCFRONTCOMPUTERFORM_H

#include <QWidget>
#include <QThread>
#include "BundleContext.h"
using namespace cppmicroservices;
namespace Ui {
class TTCFrontComputerForm;
}

class TTCFrontComputerForm : public QWidget
{
    Q_OBJECT

public:
    explicit TTCFrontComputerForm(BundleContext context,QWidget *parent = 0);
    ~TTCFrontComputerForm();
    void slot_recv(const QByteArray byte);

signals:
    void startAutoSend(int inerval);
    void stopAutoSend();

protected:
    void closeEvent(QCloseEvent *event)Q_DECL_OVERRIDE;
private slots:
    void on_pBtnSend_clicked();

    void on_pBtnClear_clicked();

    void on_checkBox_send_clicked(bool checked);

    void on_spinBox_valueChanged(int arg1);

private:
    void packData(QByteArray &data);
    void packBaseFrame(QByteArray &data);
    int sendData(const QByteArray &data);
    void initThread();

private:
    Ui::TTCFrontComputerForm *ui;
    BundleContext m_context;
    QThread m_workerThread;
};

#endif // TTCFRONTCOMPUTERFORM_H
