#-------------------------------------------------
#
# Project created by QtCreator 2020-12-07T14:59:20
#
#-------------------------------------------------

QT       += xml network serialport

QT       -= gui

include($$PWD/../../../platform/platform_lib.pri)

TARGET = CommunicationChannels
TEMPLATE = lib

DEFINES += COMMUNICATIONCHANNELS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/channels

SOURCES += \
    channels/channelbase.cpp \
    channels/udpchannel.cpp \
    channels/commchannel.cpp \
    channels/tcpchannel.cpp \
    channels/communicationbase.cpp \
    channels/tcpserverchannel.cpp \
    channels/socketindividual.cpp

HEADERS += \
        communicationchannels_global.h \ 
    channels/channelbase.h \
    channels/udpchannel.h \
    channels/commchannel.h \
    channels/tcpchannel.h \
    channels/communicationbase.h \
    channels/tcpserverchannel.h \
    channels/socketindividual.h

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/CommunicationChannels)

