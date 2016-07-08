#include "applicationsettings.h"

#include <QTimer>
#include <QSettings>
#include <QDebug>

namespace
{
    ApplicationSettings *appSettings = 0;

    const char *mainWindowGeometryKey = "mainwindow/geometry";
    const char *mainWindowStateKey = "mainwindow/windowState";
    const char *hideOnCloseKey = "mainwindow/hideonclose";
    const char *startHiddenKey = "mainwindow/starthidden";
    const char *teamDomainKey = "team_domain";
}

ApplicationSettings::ApplicationSettings(QObject *parent)
    : QObject(parent)
    , changeSignalSent(false)
{
    appSettings = this;
}

ApplicationSettings::~ApplicationSettings()
{
    appSettings = 0;
}

ApplicationSettings *ApplicationSettings::instance()
{
    return appSettings;
}

void ApplicationSettings::commit()
{
    changeSignalSent = false;
    emit changed();
    qDebug() << "Application settings changed";
}

QString ApplicationSettings::getTeamDomain() const
{
    return settings.value(teamDomainKey).toString();
}

void ApplicationSettings::setTeamDomain(const QString &value)
{
    settings.setValue(teamDomainKey, value);
    emitChange();
}

QByteArray ApplicationSettings::getMainWindowGeometry() const
{
    return settings.value(mainWindowGeometryKey).toByteArray();
}

void ApplicationSettings::setMainWindowGeometry(const QByteArray &value)
{
    settings.setValue(mainWindowGeometryKey, value);
    emitChange();
}

void ApplicationSettings::emitChange()
{
    if (changeSignalSent)
        return;

    QTimer::singleShot(0, this, SLOT(commit()));
    changeSignalSent = true;
}

QByteArray ApplicationSettings::getMainWindowState() const
{
    return settings.value(mainWindowStateKey).toByteArray();
}

void ApplicationSettings::setMainWindowState(const QByteArray &value)
{
    settings.setValue(mainWindowStateKey, value);
    emitChange();
}

bool ApplicationSettings::getStartHidden() const
{
    return settings.value(startHiddenKey).toBool();
}

void ApplicationSettings::setStartHidden(bool value)
{
    settings.setValue(startHiddenKey, value);
    emitChange();
}

bool ApplicationSettings::getHideOnClose() const
{
    return settings.value(hideOnCloseKey).toBool();
}

void ApplicationSettings::setHideOnClose(bool value)
{
    settings.setValue(hideOnCloseKey, value);
    emitChange();
}
