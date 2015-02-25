#include "mainwindow.h"
#include <QApplication>

class Application final : public QApplication {
public:
    Application(int& argc, char** argv)
        : QApplication(argc, argv)
    {

    }
    virtual bool notify(QObject *receiver, QEvent *event) override
    {
        try {

            if (receiver->objectName() == QString::fromUtf8("tr"))

            bool result = QApplication::notify(receiver, event);

            if (dynamic_cast<QTimerEvent*>(event))
            {
                return true;
            }

            qDebug() << receiver << event;

            return true;
        } catch (...) {
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);

    Application a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
