#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T18:34:28
#
#-------------------------------------------------

QT       -= gui

TARGET = CorePlatform_src
TEMPLATE = lib

DEFINES += COREPLATFORM_LIBRARY

SOURCES += coreplatform.cpp \
    platformmodule.cpp \
    baselogger.cpp

HEADERS += coreplatform.h\
        coreplatform_global.h \
    platformmodule.h \
    baselogger.h \
    controls.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#DISTFILES += \
 #   CorePlatform_src.pri

#=======include UTILS========
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Utils/debug/ -lUtils
else:unix: LIBS += -L$$OUT_PWD/../../Utils/ -lUtils

INCLUDEPATH += $$PWD/../../Utils
DEPENDPATH += $$PWD/../../Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/debug/Utils.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Utils/libUtils.a
