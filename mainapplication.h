#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QApplication>
#include "mainwindow.h"

class MainApplication : public QApplication
{
        Q_OBJECT

    public:
        explicit MainApplication(int &argc, char **argv);

        inline static MainApplication *instance()
        {
            return static_cast<MainApplication *>(QApplication::instance());
        }

        void setMainWindow(MainWindow *window);
        MainWindow *getMainWindow();

        void showNotification(QString title, QString message);

        ~MainApplication();
    private:
        MainWindow *m_window = 0;
};

#endif // MAINAPPLICATION_H
