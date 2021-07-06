#ifndef IGUISERVICE_H
#define IGUISERVICE_H

#include <QByteArray>
#include <QString>
#include <QWidget>
class IGuiServiceInterface
{
public:
    virtual ~IGuiServiceInterface() {}

    virtual QWidget* CreateGui() = 0;
    virtual void SendMessge(QByteArray byte,QString chnnaID) = 0;
};

#endif  // IGUISERVICE_H
