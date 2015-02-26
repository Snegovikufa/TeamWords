contains(QT,sensors) {
    DEFINES += ASEMAN_SENSORS
    SOURCES += asemantools/asemansensors.cpp
    HEADERS += asemantools/asemansensors.h
}
contains(QT,widgets) {
    DEFINES += NATIVE_ASEMAN_NOTIFICATION
    SOURCES +=  \
        asemantools/asemannativenotification.cpp \
        asemantools/asemannativenotificationitem.cpp
    HEADERS +=  \
        asemantools/asemannativenotification.h \
        asemantools/asemannativenotificationitem.h
}
linux {
contains(QT,dbus) {
    DEFINES += LINUX_NATIVE_ASEMAN_NOTIFICATION
    SOURCES += asemantools/asemanlinuxnativenotification.cpp
    HEADERS += asemantools/asemanlinuxnativenotification.h
}
}
macx {
    DEFINES += MAC_NATIVE_ASEMAN_NOTIFICATION
    SOURCES += asemantools/asemanmacnativenotification.cpp
    HEADERS += asemantools/asemanmacnativenotification.h
}

SOURCES += \
    asemantools/asemanqtlogger.cpp \
    asemantools/asemantools.cpp \
    asemantools/asemandesktoptools.cpp \
    asemantools/asemanlistobject.cpp \
    asemantools/asemanhashobject.cpp \
    asemantools/asemancalendarconvertercore.cpp \
    asemantools/asemancalendarconverter.cpp \
    asemantools/asemansysteminfo.cpp \
    asemantools/asemanabstractcolorfulllistmodel.cpp \
    asemantools/asemanimagecoloranalizor.cpp \
    asemantools/asemancountriesmodel.cpp \
    asemantools/asemanmimedata.cpp \
    asemantools/asemandownloader.cpp \
    asemantools/asemannotification.cpp \
    asemantools/asemanautostartmanager.cpp

HEADERS += \
    asemantools/asemanqtlogger.h \
    asemantools/asemantools.h \
    asemantools/asemandesktoptools.h \
    asemantools/asemanlistobject.h \
    asemantools/asemanhashobject.h \
    asemantools/aseman_macros.h \
    asemantools/asemancalendarconvertercore.h \
    asemantools/asemancalendarconverter.h \
    asemantools/asemansysteminfo.h \
    asemantools/asemanabstractcolorfulllistmodel.h \
    asemantools/asemanimagecoloranalizor.h \
    asemantools/asemancountriesmodel.h \
    asemantools/asemanmimedata.h \
    asemantools/asemandownloader.h \
    asemantools/asemannotification.h \
    asemantools/asemanautostartmanager.h

OTHER_FILES +=

RESOURCES += \
    asemantools/asemanresource.qrc
