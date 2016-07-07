#include "mainwindow.h"
#include "mainapplication.h"
#include "teamform.h"
#include "applicationsettings.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    MainApplication a(argc, argv);
    a.setWindowIcon(QIcon(QString("://images/png/icon32.png")));
    ApplicationSettings settings;
    MainWindow mainWindow;
    a.setMainWindow(&mainWindow);
    QString team_domain = settings.getTeamDomain();

    if (!team_domain.isEmpty())
    {
        qDebug() << "team_domain:" << team_domain;
        if (!settings.getStartHidden())
            mainWindow.show();
    }
    else
    {
        qDebug() << "no team_domain specified";
        TeamForm *teamform = new TeamForm();
        teamform->show();
    }

    return a.exec();
}
