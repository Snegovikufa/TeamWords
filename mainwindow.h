#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKitWidgets>
#include <QSystemTrayIcon>
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#include <QtWinExtras>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void featureRequest(QWebFrame *frame, QWebPage::Feature feature);
    void trayActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
