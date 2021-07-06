#-------------------------------------------------
#
# Project created by QtCreator 2020-02-27T10:32:44
#
#-------------------------------------------------

QT       += gui
QT       += widgets xml sql

TARGET = util
TEMPLATE = lib

DEFINES += UTIL_SELF_LIBRARY

include($$PWD/../../../platform/platform_lib.pri)

INCLUDEPATH += $$PWD/ActionFactory
INCLUDEPATH += $$PWD/UiFactory
INCLUDEPATH += $$PWD/ConditonFactory
INCLUDEPATH += $$PWD/common

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    util.cpp \
    common/CConstants.cpp \
    common/CConverter.cpp \
    common/UiControl.cpp \
    common/commonfunction.cpp \
    UiFactory/bcddateedit.cpp \
    UiFactory/bitcombobox.cpp \
    UiFactory/bitstatuslabel.cpp \
    UiFactory/bittimesetting.cpp \
    UiFactory/comboboxwithdouble.cpp \
    UiFactory/datacombobox.cpp \
    UiFactory/doublespinbox.cpp \
    UiFactory/fakecodecombobox.cpp \
    UiFactory/framerecordtablewidget.cpp \
    UiFactory/hexlineedit.cpp \
    UiFactory/integerdoublespinbox.cpp \
    UiFactory/integerspinbox.cpp \
    UiFactory/integerstatuslabel.cpp \
    UiFactory/layoutwidget.cpp \
    UiFactory/modeswitchwidget.cpp \
    UiFactory/paramlisttablewidget.cpp \
    UiFactory/snrdisplay.cpp \
    UiFactory/specialnagativedoublespinbox.cpp \
    UiFactory/standardtimesetting.cpp \
    UiFactory/stringlineedit.cpp \
    UiFactory/t0timesetting.cpp \
    UiFactory/timestampdisplay.cpp \
    UiFactory/uifactory.cpp \
    ActionFactory/actionfactory.cpp \
    ActionFactory/propertyaction.cpp \
    ConditonFactory/conditonfactory.cpp \
    ConditonFactory/integerequalproduct.cpp \
    ConditonFactory/integernotequalproduct.cpp \
    common/relationxmlmanager.cpp \
    common/uixmlmanager.cpp \
    common/paramwidgetimplement.cpp \
    common/labeldraw.cpp \
    json/Json.cpp \
    file/filehelper.cpp

HEADERS += \
    util.h \
    util_global.h \
    common/CConstants.h \
    common/CConverter.h \
    common/UiControl.h \
    common/commonfunction.h \
    UiFactory/bcddateedit.h \
    UiFactory/bitcombobox.h \
    UiFactory/bitstatuslabel.h \
    UiFactory/bittimesetting.h \
    UiFactory/comboboxwithdouble.h \
    UiFactory/datacombobox.h \
    UiFactory/doublespinbox.h \
    UiFactory/fakecodecombobox.h \
    UiFactory/framerecordtablewidget.h \
    UiFactory/hexlineedit.h \
    UiFactory/integerdoublespinbox.h \
    UiFactory/integerspinbox.h \
    UiFactory/integerstatuslabel.h \
    UiFactory/layoutwidget.h \
    UiFactory/modeswitchwidget.h \
    UiFactory/paramlisttablewidget.h \
    UiFactory/snrdisplay.h \
    UiFactory/specialnagativedoublespinbox.h \
    UiFactory/standardtimesetting.h \
    UiFactory/stringlineedit.h \
    UiFactory/t0timesetting.h \
    UiFactory/timestampdisplay.h \
    UiFactory/uifactory.h \
    ActionFactory/actionfactory.h \
    ActionFactory/iactionproduct.h \
    ActionFactory/propertyaction.h \
    ConditonFactory/conditonfactory.h \
    ConditonFactory/iconditonproduct.h \
    ConditonFactory/integerequalproduct.h \
    ConditonFactory/integernotequalproduct.h \
    common/relationxmlmanager.h \
    common/uixmlmanager.h \
    common/paramwidgetimplement.h \
    common/ConfigParamDefine.h \
    common/labeldraw.h \
    string2num.h \
    json/Json.h \
    file/filehelper.h

PUBLIC_HEADERS += common/CConstants.h \
                common/CConverter.h \
                common/UiControl.h \
                common/commonfunction.h \
                common/relationxmlmanager.h \
                common/uixmlmanager.h \
                common/paramwidgetimplement.h \
                common/ConfigParamDefine.h \
                UiFactory/bcddateedit.h \
                UiFactory/bitcombobox.h \
                UiFactory/bitstatuslabel.h \
                UiFactory/bittimesetting.h \
                UiFactory/comboboxwithdouble.h \
                UiFactory/datacombobox.h \
                UiFactory/doublespinbox.h \
                UiFactory/fakecodecombobox.h \
                UiFactory/framerecordtablewidget.h \
                UiFactory/hexlineedit.h \
                UiFactory/integerdoublespinbox.h \
                UiFactory/integerspinbox.h \
                UiFactory/integerstatuslabel.h \
                UiFactory/layoutwidget.h \
                UiFactory/modeswitchwidget.h \
                UiFactory/paramlisttablewidget.h \
                UiFactory/snrdisplay.h \
                UiFactory/specialnagativedoublespinbox.h \
                UiFactory/standardtimesetting.h \
                UiFactory/stringlineedit.h \
                UiFactory/t0timesetting.h \
                UiFactory/timestampdisplay.h \
                UiFactory/uifactory.h \
                ActionFactory/actionfactory.h \
                ActionFactory/iactionproduct.h \
                ActionFactory/propertyaction.h \
                util_global.h

deployModule($$HEADERS, $$GLOBAL_INCLUDE_DIR/util)

