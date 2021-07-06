#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T15:03:07
#
#-------------------------------------------------

QT       += network xml sql

QT       -= gui

TARGET = Log4Qt
TEMPLATE = lib

TRANSLATION_FILE = $$TARGET

include($$PWD/../../../platform/platform_lib.pri)

DEFINES += LIBLOG4QT_LIBRARY

INCLUDEPATH += ./

SOURCES += \
    log4qt/writerappender.cpp \
    log4qt/ttcclayout.cpp \
    log4qt/simplelayout.cpp \
    log4qt/rollingfileappender.cpp \
    log4qt/propertyconfigurator.cpp \
    log4qt/patternlayout.cpp \
    log4qt/ndc.cpp \
    log4qt/mdc.cpp \
    log4qt/logmanager.cpp \
    log4qt/loggingevent.cpp \
    log4qt/loggerrepository.cpp \
    log4qt/logger.cpp \
    log4qt/log4qt.cpp \
    log4qt/level.cpp \
    log4qt/layout.cpp \
    log4qt/hierarchy.cpp \
    log4qt/fileappender.cpp \
    log4qt/dailyrollingfileappender.cpp \
    log4qt/consoleappender.cpp \
    log4qt/basicconfigurator.cpp \
    log4qt/appenderskeleton.cpp \
    log4qt/helpers/properties.cpp \
    log4qt/helpers/patternformatter.cpp \
    log4qt/helpers/optionconverter.cpp \
    log4qt/helpers/logobjectptr.cpp \
    log4qt/helpers/logobject.cpp \
    log4qt/helpers/logerror.cpp \
    log4qt/helpers/initialisationhelper.cpp \
    log4qt/helpers/factory.cpp \
    log4qt/helpers/datetime.cpp \
    log4qt/helpers/configuratorhelper.cpp \
    log4qt/helpers/classlogger.cpp \
    log4qt/spi/filter.cpp \
    log4qt/varia/stringmatchfilter.cpp \
    log4qt/varia/nullappender.cpp \
    log4qt/varia/listappender.cpp \
    log4qt/varia/levelrangefilter.cpp \
    log4qt/varia/levelmatchfilter.cpp \
    log4qt/varia/denyallfilter.cpp \
    log4qt/varia/debugappender.cpp \
    log4qt/xmllayout.cpp \
    log4qt/jsonlayout.cpp \
    log4qt/dbappender.cpp

LOG4QT_HEADERS += \
    log4qt/writerappender.h \
    log4qt/ttcclayout.h \
    log4qt/simplelayout.h \
    log4qt/rollingfileappender.h \
    log4qt/propertyconfigurator.h \
    log4qt/patternlayout.h \
    log4qt/ndc.h \
    log4qt/mdc.h \
    log4qt/logmanager.h \
    log4qt/loggingevent.h \
    log4qt/loggerrepository.h \
    log4qt/logger.h \
    log4qt/log4qt.h \
    log4qt/level.h \
    log4qt/layout.h \
    log4qt/hierarchy.h \
    log4qt/fileappender.h \
    log4qt/dailyrollingfileappender.h \
    log4qt/consoleappender.h \
    log4qt/basicconfigurator.h \
    log4qt/appenderskeleton.h \
    log4qt/appender.h \
    log4qt/xmllayout.h \
    log4qt/jsonlayout.h \
    log4qt/typedef.h \
    log4qt/dbappender.h

HELPERS_HEADERS += \
    log4qt/helpers/properties.h \
    log4qt/helpers/patternformatter.h \
    log4qt/helpers/optionconverter.h \
    log4qt/helpers/logobjectptr.h \
    log4qt/helpers/logobject.h \
    log4qt/helpers/logerror.h \
    log4qt/helpers/initialisationhelper.h \
    log4qt/helpers/factory.h \
    log4qt/helpers/datetime.h \
    log4qt/helpers/configuratorhelper.h \
    log4qt/helpers/classlogger.h

SPI_HEADERS += log4qt/spi/filter.h

VARIA_HEADERS += \
    log4qt/varia/stringmatchfilter.h \
    log4qt/varia/nullappender.h \
    log4qt/varia/listappender.h \
    log4qt/varia/levelrangefilter.h \
    log4qt/varia/levelmatchfilter.h \
    log4qt/varia/denyallfilter.h \
    log4qt/varia/debugappender.h

HEADERS += log4qt_global.h \
    $$LOG4QT_HEADERS \
    $$HELPERS_HEADERS \
    $$SPI_HEADERS \
    $$VARIA_HEADERS \
    log4qt_init.h

cpdll.path = $$LXTSSP_FRAME_DIR/DS
cpdll.files = $$GLOBAL_LIBS_DIR/*$$TARGET.*

INSTALLS += cpdll

deployModule(log4qt.prf, $$GLOBAL_INCLUDE_DIR)
deployModule(log4qt_global.h, $$GLOBAL_INCLUDE_DIR/log4qt/)
deployModule(log4qt_init.h, $$GLOBAL_INCLUDE_DIR/log4qt/)
deployModule($$LOG4QT_HEADERS, $$GLOBAL_INCLUDE_DIR/log4qt/log4qt/)
deployModule($$HELPERS_HEADERS, $$GLOBAL_INCLUDE_DIR/log4qt/log4qt/helpers/)
deployModule($$SPI_HEADERS, $$GLOBAL_INCLUDE_DIR/log4qt/log4qt/spi/)
deployModule($$VARIA_HEADERS, $$GLOBAL_INCLUDE_DIR/log4qt/log4qt/varia/)
