greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
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
    gnssdatahandler.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    version.h \
    timegraph.h \
    gnssdatahandler.h \
    gnssdata.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    timegraph.ui

RESOURCES += \
    terminal.qrc

#include QWT
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
