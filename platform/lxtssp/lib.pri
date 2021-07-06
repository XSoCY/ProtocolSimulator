DEFINES += COMPILE_WITH_LXTSSP

LXTSSP_FRAME_DIR = $$PWD/../../

INCLUDEPATH += $$LXTSSP_FRAME_DIR/include

LIBS += -L$$LXTSSP_FRAME_DIR/libs -lLxTsspObjectManager

#全局包含文件目录
GLOBAL_INCLUDE_DIR = $$LXTSSP_FRAME_DIR/include
#全局lib文件包含目录，库文件都需要拷贝到这里
GLOBAL_LIBS_DIR = $$LXTSSP_FRAME_DIR/libs
GLOBAL_RUN_DIR = $$LXTSSP_FRAME_DIR/DS

DESTDIR = $$GLOBAL_LIBS_DIR

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
        #FILE = $$PWD/$$FILE
        win32: FILE ~= s,/,\\,g
        win32: system(cmd /c copy /y $$FILE $$DEPLOY_DIR)
        unix:!mac: system(cp $$FILE $$DEPLOY_DIR)
    }
    return(true)
}

target.path = $$GLOBAL_RUN_DIR

INSTALLS += target

