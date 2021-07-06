#ifndef TTCFRONTCOMPUTERFORM_H
#define TTCFRONTCOMPUTERFORM_H

#include <QWidget>
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
protected:
    void closeEvent(QCloseEvent *event)Q_DECL_OVERRIDE;
private slots:
    void on_pBtnSend_clicked();

    void on_pBtnClear_clicked();

private:
    void packData(QByteArray &data);
    void packBaseFrame(QByteArray &data);
    int sendData(const QByteArray &data);

private:
    Ui::TTCFrontComputerForm *ui;
    BundleContext m_context;
};

#endif // TTCFRONTCOMPUTERFORM_H
