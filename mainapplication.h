#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QApplication>
#include "mainwindow.h"

#define mApp ((MainApplication*)MainApplication::instance())

class MainApplication : public QApplication
{
    Q_OBJECT

public:
    explicit MainApplication(int &argc, char** argv);

    void setMainWindow(MainWindow* window);
    MainWindow* getMainWindow();

    void showNotification(QString title, QString message);

    ~MainApplication();
private:
    MainWindow *m_window = 0;
};

#endif // MAINAPPLICATION_H
