#-------------------------------------------------
#
# Project created by QtCreator 2020-02-27T10:32:44
#
#-------------------------------------------------

QT       -= gui
QT       += core sql

TARGET = Database
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += DATABASE_LIBRARY

include($$PWD/../../../platform/platform_lib.pri)


INCLUDEPATH += $$PWD/base
INCLUDEPATH += $$PWD/parammacro
INCLUDEPATH += $$PWD/configmacro
INCLUDEPATH += $$PWD/linkdevice

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/Log

LIBS += -L$$GLOBAL_LIBS_DIR -lLog
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    autotest/autotestresult.h \
    autotest/autoteststandard.h \
    database_global.h \
    base/sqlitedatabase.h \
    base/tbbase.h \
    device/tbdevicestatusstore.h \
    parammacro/tbparammacro.h \
    parammacro/tbparammacrosub.h \
    configmacro/tbconfigmacro.h \
    configmacro/tbconfigmacro_linkinfo.h \
    configmacro/tbconfigmacro_linkdeviceinfo.h \
    task/tbtaskinfo.h \
    task/tbtaskplanning.h \
    device/tbdeviceinfo.h \
    device/tblinkdevice.h \
    data/tbrawdata.h \
    data/tbresultdata.h \
    rule/tbrule.h

SOURCES += \
    base/sqlitedatabase.cpp \
    base/tbbase.cpp \
    device/tbdevicestatusstore.cpp \
    device/tbdeviceinfo.cpp \
    device/tblinkdevice.cpp \
    data/tbrawdata.cpp \
    data/tbresultdata.cpp \
    rule/tbrule.cpp

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/Database)
