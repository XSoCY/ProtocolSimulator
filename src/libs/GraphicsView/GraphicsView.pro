#-------------------------------------------------
#
# Project created by QtCreator 2020-12-22T12:00:28
#
#-------------------------------------------------
QT      +=  network xml
QT      += widgets

TARGET = GraphicsView
TEMPLATE = lib

DEFINES += GRAPHICSVIEW_LIBRARY

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
INCLUDEPATH += $$PWD/GraphicsView
INCLUDEPATH += $$PWD/GraphicsItem
INCLUDEPATH += $$PWD/common

LIBS += -L$$GLOBAL_LIBS_DIR -lLog

SOURCES += \
        graphicsview.cpp \
    GraphicsItem/cpixmaptextitem.cpp \
    GraphicsItem/carrowpathitem.cpp \
    xgraphicsscene.cpp \
    xgraphicsview.cpp

HEADERS += \
        graphicsview.h \
        graphicsview_global.h \
    GraphicsItem/cpixmaptextitem.h \
    GraphicsItem/carrowpathitem.h \
    xgraphicsscene.h \
    xgraphicsview.h

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/GraphicsView)


