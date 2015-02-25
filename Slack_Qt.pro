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
    mainapplication.cpp

HEADERS  += mainwindow.h \
    mainapplication.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    readme.md
