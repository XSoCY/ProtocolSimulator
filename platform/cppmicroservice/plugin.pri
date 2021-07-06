DEFINES += COMPILE_WITH_LXTSSP

FRAME_DIR = $$PWD/../../

INCLUDEPATH += $$PWD
INCLUDEPATH += $$FRAME_DIR/
INCLUDEPATH += $$FRAME_DIR/include

#全局包含文件目录
GLOBAL_INCLUDE_DIR = $$FRAME_DIR/include

#全局lib文件包含目录，库文件都需要拷贝到这里
CONFIG(debug, debug|release) {
    GLOBAL_LIBS_DIR = $$FRAME_DIR/libs/debug
    GLOBAL_RUN_DIR = $$FRAME_DIR/bin/debug/plugins
}else{
    GLOBAL_LIBS_DIR = $$FRAME_DIR/libs/release
    GLOBAL_RUN_DIR = $$FRAME_DIR/bin/release
}

DESTDIR = $$GLOBAL_LIBS_DIR

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/cppmicroservices
INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/Interface
INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/guiservices

LIBS += -L$$GLOBAL_LIBS_DIR -lCppMicroServices3d

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/Log
LIBS += -L$$GLOBAL_LIBS_DIR -lLog

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/ProtocolManager
LIBS += -L$$GLOBAL_LIBS_DIR -lProtocolManager

INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/ProtocolManager
LIBS += -L$$GLOBAL_LIBS_DIR -lProtocolManager

win32-msvc{
    QMAKE_CXXFLAGS += /utf-8
}

defineTest(deployModule) {
    DEPLOY_FILES = $$1
    DEPLOY_DIR = $$2
    win32:DEPLOY_DIR ~= s,/,\\,g

    isEmpty(DEPLOY_DIR) {
        return(false)
    }

    exists($$DEPLOY_DIR) {
    } else {
        lessThan(QT_MAJOR_VERSION, 5) {
            win32: system(cmd /c md $$DEPLOY_DIR)
            unix:!mac: system(mkdir $$DEPLOY_DIR)
        } else {
            mkpath($$DEPLOY_DIR)
        }
    }

    for(FILE, DEPLOY_FILES) {
        FILE = $$PWD/$$FILE
        win32: FILE ~= s,/,\\,g
        win32: system(cmd /c copy /y $$FILE $$DEPLOY_DIR)
        unix:!mac: system(cp $$FILE $$DEPLOY_DIR)
    }
    return(true)
}

DEFINES += Tutorial_guiservice_EXPORTS

DEFINES += US_BUNDLE_NAME=$$TARGET

DESTDIR = $$GLOBAL_RUN_DIR

#add auto run bat
win32{
    AFTER_LINK_CMD_LINE1 = cd $${FRAME_DIR} && .\tools\usResourceCompiler3.exe --compression-level 9 --verbose --bundle-name $${TARGET} --out-file $${FRAME_DIR}src/plugins/$${TARGET}/resources/res.zip --manifest-add $${FRAME_DIR}src/plugins/$${TARGET}/resources/manifest.json &&
    AFTER_LINK_CMD_LINE2 = cd $${FRAME_DIR} && .\tools\usResourceCompiler3.exe -b $${FRAME_DIR}bin/debug/plugins/$${TARGET}.dll -z $${FRAME_DIR}src/plugins/$${TARGET}/resources/res.zip
    QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE1)
    QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE2)
}

unix{
    COPY_CMD_LINE = cp  $${FRAME_DIR}/plugins/$${TARGET}/resources/manifest.json  $${FRAME_DIR}/bin/plugins/manifest.json &&
    RENAME_CMD_LINE = mv $${FRAME_DIR}/bin/debug/plugins/manifest.json $${FRAME_DIR}/bin/debug/plugins/$${TARGET}_manifest.json &&
    AFTER_LINK_CMD_LINE1 = cd $${FRAME_DIR}/bin/debug/plugins/ && usResourceCompiler3 --compression-level 9 --verbose --bundle-name $${TARGET} --out-file res.zip --manifest-add $${TARGET}_manifest.json &&
    AFTER_LINK_CMD_LINE2 = usResourceCompiler3 -b lib$${TARGET}.so -z res.zip
    QMAKE_POST_LINK += $$quote($$COPY_CMD_LINE)
    QMAKE_POST_LINK += $$quote($$RENAME_CMD_LINE)
    QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE1)
    QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE2)
}


