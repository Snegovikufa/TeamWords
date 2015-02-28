#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKitWidgets>
#include <QSystemTrayIcon>
#include <QWebNotificationData>
#include <QtNetwork/QNetworkAccessManager>
#include "qwebkitplatformplugin.h"
#include "cookiejar.h"
#include "webview.h"
#include "asemantools/asemannativenotification.h"

#ifdef Q_OS_WIN32
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#include <QtWinExtras>
#endif


class CookieJar;
class NetworkAccessManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    virtual void showEvent(QShowEvent *event)  override;
    virtual void hideEvent(QHideEvent *event)  override;
    virtual void closeEvent(QCloseEvent *event) override;

    void showNotification(QString title, QString message);

    ~MainWindow();


public slots:
    void featureRequest(QWebFrame *frame, QWebPage::Feature feature);
    void trayActivated(QSystemTrayIcon::ActivationReason reason);
    void onUrlChanged(QUrl url);

private:
    WebView *webView;
    AsemanNativeNotification *notification;

#ifdef Q_OS_WIN32
    QWinTaskbarButton *button;
#endif

    QSystemTrayIcon *trayIcon;

    const QString teamLoginUrl = QString("https://%1.slack.com");
    const QString loginUrl = QString("https://slack.com/signin");

    void createTray();
    void setIcons();
    void setUrl();
    void createWebView();
    void readSettings();
};

#endif // MAINWINDOW_H
