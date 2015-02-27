# Unix
!mac:unix {
    contains(DEFINES, USE_QTWEBKIT_2_2) {
        buildNotifications = true
    }
    else {
        buildPlugin = false
    }
}

# Mac OS X
mac {
    buildPlugin = false
}

# OS/2
os2 {
    buildPlugin = false
}

linux {
    buildPlugin = true
    buildNotifications = true
}

# Windows
win32 {
    win32-msvc* {
        # QtWebKit 2.3 and Hunspell is now needed to build on Windows
        buildNotifications = true
    }
    else { # mingw
        buildPlugin = false
    }
}

message(Build plugin? $$buildPlugin)
!equals(buildPlugin, false) {
    HEADERS += $$PWD/qtwebkitplugin.h \
               $$[QT_INSTALL_HEADERS]/QtWebKit/qwebkitplatformplugin.h

    SOURCES += $$PWD/qtwebkitplugin.cpp

    DEFINES *= QT_STATICPLUGIN
}
else {
    buildNotifications = false
}

message(Build notifications? $$buildNotifications)
equals(buildNotifications, true) {
    HEADERS += $$PWD/notifications/notificationpresenter.h
    SOURCES += $$PWD/notifications/notificationpresenter.cpp
}

INCLUDEPATH += $$top_srcdir
HEADERS += $$top_srcdir/mainapplication.h

