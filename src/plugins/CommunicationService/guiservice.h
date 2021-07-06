#ifndef GUISERVICE_H
#define GUISERVICE_H
#include "IGuiService.h"
#include "BundleContext.h"
#include "communicationservicebase.h"

#include <QByteArray>
#include <QMap>
class MainWindow;
using namespace cppmicroservices;

class CommunicationServiceImpl;

class GuiService : public QObject, public IGuiServiceInterface
{
    Q_OBJECT
public:
    GuiService(BundleContext context);
    ~GuiService();
    QWidget* CreateGui();
    void SendMessge(QByteArray byte,QString chnnaID);
    MainWindow* getMainWid()
    {
        return m_widget;
    }
private:
    BundleContext               m_context;
    MainWindow *m_widget;
};
#endif  // GUISERVICE_H
