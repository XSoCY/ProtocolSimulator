DEFINES += COMPILE_WITH_LXTSSP

FRAME_DIR = $$PWD/../../

INCLUDEPATH += $$FRAME_DIR/include

#全局包含文件目录
GLOBAL_INCLUDE_DIR = $$FRAME_DIR/include
#全局lib文件包含目录，库文件都需要拷贝到这里
CONFIG(debug, debug|release) {
    GLOBAL_LIBS_DIR = $$FRAME_DIR/libs/debug
    GLOBAL_RUN_DIR = $$FRAME_DIR/bin/debug
}else{
    GLOBAL_LIBS_DIR = $$FRAME_DIR/libs/release
    GLOBAL_RUN_DIR = $$FRAME_DIR/bin/release
}

DESTDIR = $$GLOBAL_LIBS_DIR

!contains(DEFINES, LOG_LIBRARY){
    INCLUDEPATH += $$GLOBAL_INCLUDE_DIR/Log
    LIBS += -L$$GLOBAL_LIBS_DIR -lLog
}

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

