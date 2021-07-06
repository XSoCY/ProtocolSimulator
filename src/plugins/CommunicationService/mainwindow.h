#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BundleContext.h"
using namespace cppmicroservices;

namespace Ui {
class MainWindow;
}
class SQLTableForm;
class TTCcombinationForm;
class TTCFrontComputerForm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(BundleContext context,QWidget *parent = 0);
    ~MainWindow();
    SQLTableForm* get_SQLTableForm()
    {
        return m_SQLTableForm;
    }
    void sendData(QByteArray byte,QString chnnaID);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    BundleContext m_context;
    SQLTableForm *m_SQLTableForm;
    TTCcombinationForm *m_TTCcombinationForm;
    TTCFrontComputerForm *m_TTCFrontComputerForm;
};

#endif // MAINWINDOW_H
