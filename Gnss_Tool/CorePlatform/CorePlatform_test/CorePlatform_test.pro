QT       += testlib

QT       -= gui

TARGET = tst_coreplatform_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_coreplatform_test.cpp \
    testplatform.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    testplatform.h

#=======include CorePlatform========
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CorePlatform_src/release/ -lCorePlatform_src
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CorePlatform_src/debug/ -lCorePlatform_src
else:unix: LIBS += -L$$OUT_PWD/../CorePlatform_src/ -lCorePlatform_src

INCLUDEPATH += $$PWD/../CorePlatform_src
DEPENDPATH += $$PWD/../CorePlatform_src

#=======include Utils========

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Utils/debug/ -lUtils
else:unix:!macx: LIBS += -L$$OUT_PWD/../../Utils/ -lUtils

INCLUDEPATH += $$PWD/../../Utils
DEPENDPATH += $$PWD/../../Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Utils/debug/Utils.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../Utils/libUtils.a
