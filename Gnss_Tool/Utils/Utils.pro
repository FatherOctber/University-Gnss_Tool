#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T19:53:55
#
#-------------------------------------------------

QT       -= gui

TARGET = Utils
TEMPLATE = lib
CONFIG += staticlib

SOURCES += utils.cpp \
    settingsreader.cpp

HEADERS += utils.h \
    settingsreader.h \
    gnssdata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
