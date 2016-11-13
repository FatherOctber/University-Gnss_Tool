include(../GPStationServer_src/GPStationServer_src.pri)

QT       += testlib network

QT       -= gui

TARGET = tst_testmain
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testmain.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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
#============================
