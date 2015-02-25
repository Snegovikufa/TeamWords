#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:40:08
#
#-------------------------------------------------

QT       += core gui network widgets webkitwidgets winextras

TARGET = Slack_Qt
TEMPLATE = app

include(plugins/qtwebkit/qtwebkit-plugins.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    mainapplication.cpp \
    cookiejar.cpp \
    autosaver.cpp \
    networkaccessmanager.cpp \
    teamform.cpp

HEADERS  += mainwindow.h \
    mainapplication.h \
    cookiejar.h \
    autosaver.h \
    networkaccessmanager.h \
    teamform.h

FORMS    += mainwindow.ui \
    teamform.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    readme.md
