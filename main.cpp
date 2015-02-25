#include "mainwindow.h"
#include "mainapplication.h"
#include "teamform.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);

    MainApplication a(argc, argv);

    QSettings settings;
    QVariant team_domain = settings.value("team_domain");
    if (team_domain.isValid()){
        qDebug() << "team_domain:" << team_domain;
        a.getMainWindow()->show();
    } else{
        qDebug() << "no team_domain specified";
        TeamForm* teamform = new TeamForm();
        teamform->show();
    }

    return a.exec();
}
