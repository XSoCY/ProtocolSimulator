TEMPLATE = lib

QT       += core gui
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += xml network serialport sql


CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += COMMUNICATIONSERVICE_LIBRARY

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = CommunicationService

include($$PWD/../../../platform/platform_plugin.pri)

INCLUDEPATH += $$PWD/communication
INCLUDEPATH += $$PWD/interpret
INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/CommunicationChannels
LIBS += -L$$GLOBAL_LIBS_DIR -lCommunicationChannels

LIBS += -llibmysql -lutil

SOURCES += \
    activator.cpp \
    communication/communicationservicebase.cpp \
    communication/communication_tcphandle.cpp \
    communication/communication_equipment.cpp \
    guiservice.cpp \
    sqltableform.cpp \
    communicationservice.cpp \
    communication/ttcfrontcomputer.cpp \
    communication/ttccombination.cpp \
    mainwindow.cpp \
    ttccombinationform.cpp \
    ttcfrontcomputerform.cpp \
    worker.cpp

HEADERS += \
    avtivator.h \
    communication/communication_define.h \
    communication/communicationservicebase.h \
    communication/communication_tcphandle.h \
    communication/communication_equipment.h \
    guiservice.h \
    sqltableform.h \
    communicationservice.h \
    communication/ttcfrontcomputer.h \
    communication/ttccombination.h \
    mainwindow.h \
    ttccombinationform.h \
    ttcfrontcomputerform.h \
    worker.h

OTHER_FILES += \
    resources/manifest.json

FORMS += \
    sqltableform.ui \
    mainwindow.ui \
    ttccombinationform.ui \
    ttcfrontcomputerform.ui

