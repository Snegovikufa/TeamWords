#include "webview.h"
#include "webpage.h"
#include <QStandardPaths>

WebView::WebView(QWidget* parent, CookieJar* cookieJar) :
    QWebView(parent),
    cookieJar(cookieJar)
{
    WebPage* page = new WebPage();
    page->setView(this);
    this->setPage(page);

    settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    settings()->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
    settings()->setAttribute(QWebSettings::NotificationsEnabled, true);
    settings()->setThirdPartyCookiePolicy(QWebSettings::ThirdPartyCookiePolicy::AlwaysAllowThirdPartyCookies);

    settings()->setFontFamily(QWebSettings::StandardFont, "Segoe UI");
    settings()->setFontSize(QWebSettings::DefaultFontSize, 16);

    setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

    setStoragePath();
    setCookies();
}

WebView::~WebView()
{
}

void WebView::setCookies()
{
    if (!cookieJar)
    {
        cookieJar = new CookieJar(this);
    }

    page()->networkAccessManager()->setCookieJar(cookieJar);
}

void WebView::setStoragePath()
{
    QString path(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    qDebug() << "Cache path" << path;

    storagePath = path;
    page()->settings()->enablePersistentStorage(storagePath);
}

