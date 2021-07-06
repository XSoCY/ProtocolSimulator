#include "mainwindow.h"
#include "Bundle.h"
#include "BundleActivator.h"
#include "BundleContext.h"
#include "Constants.h"
#include "ServiceEvent.h"
#include "filehelper.h"

#include "IGuiService.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QMetaType>
#include <QString>
#include <QVector>

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */

#include <QThread>
MainWindow::MainWindow(BundleContext context, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), context_(context)
{
    ui->setupUi(this);

    //    AAA A ;
    //    // load xml ,
    //    // 加载菜单
    //    // show ???
    //    a.Config(context_,this);

    qDebug() << "MainWindow Thread id" << QThread::currentThread();
#ifdef _WIN32
    //! Windows netword DLL init
//    WORD version = MAKEWORD(2, 2);
//    WSADATA data;

//    if (WSAStartup(version, &data) != 0) {
//    }
#endif /* _WIN32 */

    //cpp_redis::client client;
    //    client.connect();

    //    client.set("hello", "42");
    //    client.get("hello", [](cpp_redis::reply &reply) { qDebug() << reply; });
    //    qDebug() << "???";

    qRegisterMetaType<ServiceReferenceU>("ServiceReferenceU");

    listener_token_ = context_.AddServiceListener([=](const ServiceEvent &event) {
        std::string objectClass =
            ref_any_cast<std::vector<std::string>>(
                event.GetServiceReference().GetProperty(Constants::OBJECTCLASS))
                .front();

        if (event.GetType() == ServiceEvent::SERVICE_REGISTERED) {
            qDebug() << "Ex1: Service of type " << QString::fromStdString(objectClass)
                     << " registered.";
            signalInstallGuiServices(event.GetServiceReference());
        }
        else if (event.GetType() == ServiceEvent::SERVICE_UNREGISTERING) {
            qDebug() << "Ex1: Service of type " << QString::fromStdString(objectClass)
                     << " unregistered.";

            signalUninstallGuiServices(event.GetServiceReference());
        }
        else if (event.GetType() == ServiceEvent::SERVICE_MODIFIED) {
            qDebug() << "Ex1: Service of type " << QString::fromStdString(objectClass)
                     << " modified.";
            signalUninstallGuiServices(event.GetServiceReference());
            signalInstallGuiServices(event.GetServiceReference());
        }
    });

    connect(ui->dialog, &QPushButton::clicked, this, [=]() {
        std::vector<ServiceReferenceU> refs = context_.GetServiceReferences("");

        for (auto ref : refs) {
            qDebug() << "dialog " << ref.GetProperty("objectclass").ToString().c_str();
            if (QString("[IGuiService]") == ref.GetProperty("objectclass").ToString().c_str()) {
                qDebug() << "????";
                std::shared_ptr<IGuiService> gui_service = context_.GetService<IGuiService>(ref);

                qDebug() << "dialog  symbolicName " << ref.GetBundle().GetSymbolicName().c_str();
                if (gui_service.get()
                    && ref.GetBundle().GetSymbolicName() == "MicroServiceManager") {
                    if (gui_service_hash_to_widget_.contains(ref.GetBundle().GetBundleId())) {
                        gui_service_hash_to_widget_[ref.GetBundle().GetBundleId()]->show();
                    }
                    /*else{

                }
                if (auto dialog = qobject_cast<QDialog *>(gui_service->createWidget(this))) {
                    qDebug() << ;
                    dialog->show();
                }*/
                }
            }
        }
    });
    connect(ui->showTestWidget, &QPushButton::clicked, this, [=]() {
        std::vector<ServiceReferenceU> refs = context_.GetServiceReferences("");

        for (auto ref : refs) {
            qDebug() << "dialog " << ref.GetProperty("objectclass").ToString().c_str();
            if (QString("[IGuiService]") == ref.GetProperty("objectclass").ToString().c_str()) {
                qDebug() << "????";
                std::shared_ptr<IGuiService> gui_service = context_.GetService<IGuiService>(ref);

                qDebug() << "dialog  symbolicName " << ref.GetBundle().GetSymbolicName().c_str();
                if (gui_service.get() && ref.GetBundle().GetSymbolicName() == "TestWidget") {
                    if (gui_service_hash_to_widget_.contains(ref.GetBundle().GetBundleId())) {
                        gui_service_hash_to_widget_[ref.GetBundle().GetBundleId()]->show();
                    }
                    /*else{

                }
                if (auto dialog = qobject_cast<QDialog
                *>(gui_service->createWidget(this))) {
                    qDebug() << ;
                    dialog->show();
                }*/
                }
            }
        }
    });

    connect(ui->restart, &QPushButton::clicked, this, [=]() {
        for (const auto &ref : widget_to_gui_service_ref_) {
            auto &&bundle = ref.GetBundle();
            bundle.Stop();
            bundle.Start();
        }
    });

    connect(ui->install, &QPushButton::clicked, this, [=]() {
        auto pluginsDir =
            QApplication::applicationDirPath() + QDir::separator() + "plugins" + QDir::separator();
        QList<QString> pluginLists;
#if defined(Q_OS_LINUX)

        FileHelper::GetDirFileByFilters(pluginsDir, { "*.so" }, pluginLists);
#else
        FileHelper::GetDirFileByFilters(pluginsDir, { "*.dll" }, pluginLists);
#endif

        for (auto pluginFile : pluginLists) {

            auto new_bundles = context_.InstallBundles(pluginFile.toStdString());
            for (auto new_bundle : new_bundles) {
                new_bundle.Start();
            }
        }
    });

    connect(ui->uninstall, &QPushButton::clicked, this, [=]() {
        std::vector<ServiceReferenceU> refs = context_.GetServiceReferences("");

        for (auto ref : refs) {
            auto &&bundle = ref.GetBundle();
            if (bundle.GetSymbolicName().c_str() != QString("system_bundle")
                && (bundle.GetState() == Bundle::STATE_ACTIVE
                    || bundle.GetState() == Bundle::STATE_INSTALLED))
                bundle.Uninstall();
        }
    });

    connect(this,
            &MainWindow::signalUninstallGuiServices,
            this,
            &MainWindow::uninstallGuiServices,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::signalInstallGuiServices,
            this,
            &MainWindow::installGuiServices,
            Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    context_.RemoveListener(std::move(listener_token_));
    delete ui;
}

void MainWindow::installGuiServices(ServiceReferenceU service_ref)
{
    context_.GetService(service_ref);
    std::vector<std::string> vs =  service_ref.GetPropertyKeys();
    for(int i=0; i<vs.size(); ++i)
    {
        qDebug() << "service_ref.GetPropertyKeys: " << i << ":" << vs[i].c_str()//("objectclass").ToString().c_str();
                << "value: " << service_ref.GetProperty(vs[i]).ToString().c_str()
                << " interfaceId: " << service_ref.GetBundle().GetBundleId();
    }
    if (QString("[IGuiService]") == service_ref.GetProperty("objectclass").ToString().c_str()) {
        std::shared_ptr<IGuiService> gui_service = context_.GetService<IGuiService>(service_ref);
        if (gui_service.get()) {
            if (auto dialog = qobject_cast<QDialog *>(gui_service->createWidget(this))) {

                gui_service_hash_to_widget_.insert(service_ref.GetBundle().GetBundleId(), dialog);
                widget_to_gui_service_ref_.insert(dialog, service_ref);
            }
        }
    }
}

void MainWindow::uninstallGuiServices(ServiceReferenceU service_ref)
{
    if (gui_service_hash_to_widget_.contains(service_ref.GetBundle().GetBundleId())) {
        auto widget = gui_service_hash_to_widget_.value(service_ref.GetBundle().GetBundleId());
        widget->deleteLater();
        gui_service_hash_to_widget_.remove(service_ref.GetBundle().GetBundleId());
        widget_to_gui_service_ref_.remove(widget);
    }
}

void MainWindow::on_pushButton_clicked()
{
    Student s(ui->name->text().toStdString(),
              ui->age->text().toInt(),
              ui->height->text().toDouble(),
              true);

//    JsonWriter writer;
//    writer &s;
//    auto json = writer.GetString();
//    ui->jsonbuff->setPlainText(json);
}

void MainWindow::on_pushButton_2_clicked()
{
//    Student s;
//    JsonReader reader(ui->jsonbuff->toPlainText().toStdString().c_str());
//    reader &s;
//    ui->name->setText(QString::fromStdString(s.name));
//    ui->age->setText(QString::number(s.age));
//    ui->height->setText(QString::number(s.height));
}

void MainWindow::on_testService_clicked()
{

}
