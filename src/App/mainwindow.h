#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BundleContext.h"
#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

using namespace cppmicroservices;

struct Student
{
    Student() : name(), age(), height(), canSwim() {}
    Student(const std::string name, unsigned age, double height, bool canSwim)
        : name(name), age(age), height(height), canSwim(canSwim)
    {
    }

    std::string name;
    unsigned age;
    double height;
    bool canSwim;
};

template <typename Archiver>
Archiver &operator&(Archiver &ar, Student &s)
{
    ar.StartObject();
    ar.Member("name") & s.name;
    ar.Member("age") & s.age;
    ar.Member("height") & s.height;
    ar.Member("canSwim") & s.canSwim;
    return ar.EndObject();
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(BundleContext context, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalInstallGuiServices(ServiceReferenceU service_ref);
    void signalUninstallGuiServices(ServiceReferenceU service_ref);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_testService_clicked();

private:
    void installGuiServices(ServiceReferenceU service_ref);
    void uninstallGuiServices(ServiceReferenceU service_ref);

private:
    Ui::MainWindow *ui;
    QMap<QString, QDialog *> guiMap;
    QMap<std::size_t, QDialog *> gui_service_hash_to_widget_;
    QMap<QDialog *, ServiceReferenceU> widget_to_gui_service_ref_;

    BundleContext context_;
    ListenerToken listener_token_;
};
#endif  // MAINWINDOW_H
