#include "Bundle.h"
#include "BundleContext.h"
#include "BundleImport.h"
#include "Framework.h"
#include "FrameworkEvent.h"
#include "FrameworkFactory.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include "IGuiService.h"
using namespace cppmicroservices;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FrameworkFactory factory;
    auto framework = factory.NewFramework();

    try {
        framework.Start();

        auto plugin_path = QApplication::applicationDirPath() + QDir::separator() + "plugins";

        for (auto file : QDir(plugin_path).entryInfoList(QStringList() << "*.dll", QDir::Files)) {
            qDebug() << "files" << file.absoluteFilePath();
            framework.GetBundleContext().InstallBundles(file.absoluteFilePath().toStdString());
        }

        for (auto &bundles : framework.GetBundleContext().GetBundles()) {
            bundles.Start();
        }
    }
    catch (const std::exception &e) {
        qCritical() << "error:" << e.what();
        return 1;
    }

    auto context = framework.GetBundleContext();



    auto serviceRef = context.GetServiceReference<IGuiServiceInterface>();

    std::shared_ptr<IGuiServiceInterface> gui_service =
        context.GetService<IGuiServiceInterface>(serviceRef);
    if (gui_service.get())
    {
        QWidget *pw = gui_service->CreateGui();
        pw->show();
    }
    else {
        qDebug() << "error";
    }


    auto ret = a.exec();

    for (auto &bundles : framework.GetBundleContext().GetBundles()) {
        bundles.Stop();
    }
    return ret;
}
