#-------------------------------------------------
#
# Project created by QtCreator 2020-12-22T12:00:28
#
#-------------------------------------------------
QT      +=  network
QT       -= gui

TARGET = httpResponseManager
TEMPLATE = lib

DEFINES += HTTPRESPONSEMANAGER_LIBRARY

include($$PWD/../../../platform/platform_lib.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/Log
INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/util

LIBS += -L$$GLOBAL_LIBS_DIR -lLog
LIBS += -L$$GLOBAL_LIBS_DIR -lutil

SOURCES += \
        httpresponsemanager.cpp \
    sysfaulttreemanager.cpp \
    httpresponsebase.cpp \
    usermanager.cpp \
    menucontrolmanager.cpp

HEADERS += \
        httpresponsemanager.h \
        httpresponsemanager_global.h \ 
    sysfaulttreemanager.h \
    httpresponsebase.h \
    usermanager.h \
    menucontrolmanager.h \
    errorcode.h

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/httpResponseManager)
