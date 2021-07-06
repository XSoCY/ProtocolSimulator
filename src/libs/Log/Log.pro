#-------------------------------------------------
#
# Project created by QtCreator 2020-04-23T14:42:48
#
#-------------------------------------------------

QT       -= gui
QT       += xml

TARGET = Log
TEMPLATE = lib

DEFINES += LOG_LIBRARY

include($$PWD/../../../platform/platform_lib.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/log4qt
LIBS += -L$$GLOBAL_LIBS_DIR -llog4qt

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        log.cpp

HEADERS += \
        log.h \
        log_global.h 

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/Log)

