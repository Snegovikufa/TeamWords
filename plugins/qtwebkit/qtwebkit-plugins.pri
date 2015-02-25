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

!equals(buildPlugin, false) {
    HEADERS += $$PWD/qtwebkitplugin.h \
               $$[QT_INSTALL_HEADERS]/QtWebKit/qwebkitplatformplugin.h

    SOURCES += $$PWD/qtwebkitplugin.cpp

    DEFINES *= QT_STATICPLUGIN
}
else {
    buildNotifications = false
}

equals(buildNotifications, true) {
    HEADERS += $$PWD/notifications/notificationpresenter.h
    SOURCES += $$PWD/notifications/notificationpresenter.cpp
}

INCLUDEPATH += $$top_srcdir
HEADERS += $$top_srcdir/mainapplication.h

