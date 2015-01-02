#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T19:39:45
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = rest-app
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    runner.cpp \
    testrunner.cpp

HEADERS += \
    runner.h \
    testrunner.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../rest-client/release/ -lrest-client
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../rest-client/debug/ -lrest-client
else:unix: LIBS += -L$$OUT_PWD/../rest-client/ -lrest-client

INCLUDEPATH += $$PWD/../rest-client
DEPENDPATH += $$PWD/../rest-client

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rest-client/release/librest-client.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rest-client/debug/librest-client.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rest-client/release/rest-client.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../rest-client/debug/rest-client.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../rest-client/librest-client.a
