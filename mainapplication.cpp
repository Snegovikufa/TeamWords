#include "mainapplication.h"

MainApplication::MainApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    QCoreApplication::setOrganizationName("MiT-Ufa");
    QCoreApplication::setOrganizationDomain("mit-ufa.com");
    QCoreApplication::setApplicationName("TeamWords");
}

void MainApplication::setMainWindow(MainWindow *window)
{
    m_window = window;
}

MainWindow *MainApplication::getMainWindow()
{
    return m_window;
}

void MainApplication::showNotification(QString title, QString message)
{
    getMainWindow()->showNotification(title, message);
}

MainApplication::~MainApplication()
{
}

