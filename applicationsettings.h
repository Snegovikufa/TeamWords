#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>

class ApplicationSettings : public QObject
{
        Q_OBJECT
    public:
        explicit ApplicationSettings(QObject *parent = 0);
        ~ApplicationSettings();

        static ApplicationSettings *instance();

        bool getHideOnClose() const;
        void setHideOnClose(bool value);

        bool getStartHidden() const;
        void setStartHidden(bool value);

        QByteArray getMainWindowState() const;
        void setMainWindowState(const QByteArray &value);

        QByteArray getMainWindowGeometry() const;
        void setMainWindowGeometry(const QByteArray &value);

        QString getTeamDomain() const;
        void setTeamDomain(const QString& value);

signals:
        void changed();

private slots:
        void commit();

    private:
        void emitChange();

        QSettings settings;
        bool changeSignalSent;
};

#endif // APPLICATIONSETTINGS_H
