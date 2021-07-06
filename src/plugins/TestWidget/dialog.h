#ifndef DIALOG_H
#define DIALOG_H

#include "BundleContext.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Dialog;
}
QT_END_NAMESPACE

using namespace cppmicroservices;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(BundleContext context, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    BundleContext m_context;
};
#endif  // DIALOG_H
