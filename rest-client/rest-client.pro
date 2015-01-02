#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T19:18:39
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = rest-client
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

SOURCES += restclient.cpp \
    resturlbuilder.cpp \
    requesterror.cpp \
    utils/strings.cpp \
    auth/credentials.cpp \
    auth/basiccredentials.cpp

HEADERS += restclient.h \
    resturlbuilder.h \
    requesterror.h \
    utils/strings.h \
    auth/credentials.h \
    auth/basiccredentials.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
