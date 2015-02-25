#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebPage>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtWin::enableBlurBehindWindow(this);

    ui->webView->page()->settings()->enablePersistentStorage("G:\\Devel\\lol");
    ui->webView->settings()->setThirdPartyCookiePolicy(
                QWebSettings::ThirdPartyCookiePolicy::AlwaysAllowThirdPartyCookies);

    QIcon icon(QPixmap(QString::fromUtf8("://images/png/icon32.png")));
    trayIcon = new QSystemTrayIcon(icon, this);
    trayIcon->show();
    setWindowIcon(icon);

    connect(ui->webView->page(), SIGNAL(featurePermissionRequested(QWebFrame*,QWebPage::Feature)),
            this, SLOT(featureRequest(QWebFrame*,QWebPage::Feature)));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason )),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trayIcon;
}

void MainWindow::featureRequest(QWebFrame *frame, QWebPage::Feature feature)
{
    qDebug() << feature << QWebPage::Feature::Notifications;
    if (feature == QWebPage::Feature::Notifications)
    {
        ui->webView->page()->setFeaturePermission(frame, feature,
                                                  QWebPage::PermissionPolicy::PermissionGrantedByUser);
    }
}

void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
        {
            if(isHidden())
                show();
            else
                hide();
            break;
        }
        default: break;
    }
}
