greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport network
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = GPStationServer_src
TEMPLATE = app

CONFIG += qwt

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    timegraph.cpp \
    abstractserver.cpp \
    gpstationserver.cpp \
    datahandler.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    version.h \
    timegraph.h \
    abstractserver.h \
    gpstationserver.h \
    datahandler.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    timegraph.ui

RESOURCES += \
    terminal.qrc

#=======include QWT========
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/src
DEPENDPATH += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/libqwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/libqwtd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/qwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/qwtd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../../../Qt/qwt-6.1.3/lib/libqwt.a
#===========================

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
#===========================

DISTFILES += \
    GPStationServer_src.pri
