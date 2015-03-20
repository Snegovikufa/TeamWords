#include "mainwindow.h"

#include <QStandardPaths>
#include <QWebPage>
#include <QtCore>
#include <QtNetwork/QNetworkAccessManager>
#include <QWebSettings>
#include <QFontDatabase>
#include <QFileInfo>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createWebView();
    setUrl();
    createTray();
    setIcons();
#ifdef Q_OS_WIN32
    button = new QWinTaskbarButton(this);
    button->setWindow(this->windowHandle());
    button->setOverlayIcon(QIcon("://images/png/Slack.png"));
#endif
    notification = new AsemanNativeNotification(this);
    readSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::readSettings()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    this->resize(rec.width() * 0.75, rec.height() * 0.75);
    this->setMinimumSize(600, 300);
    QSettings settings;
    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    restoreState(settings.value("mainwindow/windowState").toByteArray());
}

void MainWindow::createWebView()
{
    webView = new WebView(this);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(webView);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    connect(webView->page(), SIGNAL(featurePermissionRequested(QWebFrame *, QWebPage::Feature)),
            this, SLOT(featureRequest(QWebFrame *, QWebPage::Feature)));
    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(onUrlChanged(QUrl)));
}

void MainWindow::createTray()
{
    trayIcon = new QSystemTrayIcon(QIcon(QString("://images/png/icon32.png")), this);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::setIcons()
{
    setWindowIcon(QIcon(QString("://images/png/icon32.png")));
}

void MainWindow::setUrl()
{
    QSettings settings;
    QVariant value = settings.value("team_domain");
    QUrl url(loginUrl);

    if (value.isValid())
    {
        url = QUrl(teamLoginUrl.arg(value.toString()));
    }

    qDebug() << "Team login URL: " << url;
    webView->setUrl(url);
}

void MainWindow::onUrlChanged(QUrl url)
{
    qDebug() << url.host();

    if (url.host().endsWith(".slack.com", Qt::CaseSensitive))
    {
        webView->page()->setFeaturePermission(webView->page()->mainFrame(), QWebPage::Feature::Notifications,
                                              QWebPage::PermissionPolicy::PermissionGrantedByUser);
    }
}

void MainWindow::featureRequest(QWebFrame *frame, QWebPage::Feature feature)
{
    qDebug() << frame->url();

    if (feature == QWebPage::Feature::Notifications)
    {
        int result = QMessageBox::question(this,
                                           QString("Notification permission"),
                                           QString("%1\nasks for notifications persmission. Should I allow?").arg(frame->url().toString()),
                                           QMessageBox::StandardButton::Ok, QMessageBox::Cancel);

        if (result == QMessageBox::StandardButton::Ok)
        {
            webView->page()->setFeaturePermission(frame, feature,
                                                  QWebPage::PermissionPolicy::PermissionGrantedByUser);
        }
    }
}

void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    {
        if (isHidden())
            show();
        else
            hide();

        break;
    }

    default:
        break;
    }
}

void MainWindow::showNotification(QString title, QString message)
{
    notification->sendNotify(title, message, "://images/png/Slack.png", 0, 100000);
    QApplication::alert(this);
}

void MainWindow::hideEvent(QHideEvent *event)
{
    QMainWindow::hideEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("mainwindow/geometry", saveGeometry());
    settings.setValue("mainwindow/windowState", saveState());
    trayIcon->hide();
    QMainWindow::closeEvent(event);
}
