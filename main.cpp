#include "mainwindow.h"
#include "mainapplication.h"

#define mApp MainApplication::instance()

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);

    MainApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
