#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:40:08
#
#-------------------------------------------------

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])
message(Translation files: $$[QT_INSTALL_TRANSLATIONS])
message(Settings: $$[QT_INSTALL_SETTINGS])

QT += core gui network widgets webkitwidgets

win32 {
    QT += winextras
}

TARGET = teamwords
TEMPLATE = app
CONFIG += c++11

include(asemantools/asemantools.pri)
include(plugins/qtwebkit/qtwebkit-plugins.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    mainapplication.cpp \
    cookiejar.cpp \
    autosaver.cpp \
    teamform.cpp \
    webview.cpp \
    webpage.cpp \
    applicationsettings.cpp

HEADERS  += mainwindow.h \
    mainapplication.h \
    cookiejar.h \
    autosaver.h \
    teamform.h \
    webview.h \
    webpage.h \
    applicationsettings.h

FORMS    += mainwindow.ui \
    teamform.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    readme.md \
    fonts/Lato-Black.ttf \
    fonts/Lato-BlackItalic.ttf \
    fonts/Lato-Bold.ttf \
    fonts/Lato-BoldItalic.ttf \
    fonts/Lato-Hairline.ttf \
    fonts/Lato-HairlineItalic.ttf \
    fonts/Lato-Heavy.ttf \
    fonts/Lato-HeavyItalic.ttf \
    fonts/Lato-Italic.ttf \
    fonts/Lato-Light.ttf \
    fonts/Lato-LightItalic.ttf \
    fonts/Lato-Medium.ttf \
    fonts/Lato-MediumItalic.ttf \
    fonts/Lato-Regular.ttf \
    fonts/Lato-Semibold.ttf \
    fonts/Lato-SemiboldItalic.ttf \
    fonts/Lato-Thin.ttf \
    fonts/Lato-ThinItalic.ttf \
    .astylerc

win32::RC_ICONS += images/ico/slack.ico
