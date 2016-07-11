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

#include "applicationsettings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , userWantsToClose(false)
{
    createWebView();
    setUrl();
    createActions();
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
    ApplicationSettings *settings = ApplicationSettings::instance();
    restoreGeometry(settings->getMainWindowGeometry());
    restoreState(settings->getMainWindowState());
    bool hideOnClose = settings->getHideOnClose();
    hideOnCloseAction->setChecked(hideOnClose);
    bool startHidden = settings->getStartHidden();
    startHiddenAction->setChecked(startHidden);
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
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(hideOnCloseAction);
    trayIconMenu->addAction(startHiddenAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(reloadAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(exitAction);
    trayIcon = new QSystemTrayIcon(QIcon(QString("://images/png/icon32.png")), this);
    trayIcon->setContextMenu(trayIconMenu);
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
    QString teamDomain = ApplicationSettings::instance()->getTeamDomain();
    QUrl url(loginUrl);

    if (!teamDomain.isEmpty())
    {
        url = QUrl(teamLoginUrl.arg(teamDomain));
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

void MainWindow::hideOnCloseChanged(bool value)
{
    ApplicationSettings::instance()->setHideOnClose(value);
}

void MainWindow::startHiddenChanged(bool value)
{
    ApplicationSettings::instance()->setStartHidden(value);
}

void MainWindow::realClose()
{
    userWantsToClose = true;
    close();
}

void MainWindow::reload()
{
    webView->reload();
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

void MainWindow::createActions()
{
    hideOnCloseAction = new QAction(tr("Hide on close"), this);
    hideOnCloseAction->setCheckable(true);
    connect(hideOnCloseAction, SIGNAL(toggled(bool)), this, SLOT(hideOnCloseChanged(bool)));
    startHiddenAction = new QAction(tr("Start hidden"), this);
    startHiddenAction->setCheckable(true);
    connect(startHiddenAction, SIGNAL(toggled(bool)), this, SLOT(startHiddenChanged(bool)));
    reloadAction = new QAction(tr("Reload"), this);
    connect(reloadAction, SIGNAL(triggered()), this, SLOT(reload()));
    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(realClose()));
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

void MainWindow::saveSettings()
{
    ApplicationSettings *settings = ApplicationSettings::instance();
    settings->setMainWindowGeometry(saveGeometry());
    settings->setMainWindowState(saveState());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (ApplicationSettings::instance()->getHideOnClose())
    {
        if (userWantsToClose)
        {
            saveSettings();
            trayIcon->hide();
            QMainWindow::closeEvent(event);
        }
        else
        {
            qDebug() << "User doesn't want to close";
            event->ignore();
            QMainWindow::hide();
        }
    }
    else
    {
        saveSettings();
        trayIcon->hide();
        QMainWindow::closeEvent(event);
    }
}
