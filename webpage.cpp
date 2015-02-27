#include "webpage.h"
#include <QDesktopServices>
#include <QWebFrame>
#include <QNetworkRequest>

WebPage::WebPage(QObject *parent) : QWebPage(parent)
{

}

WebPage::~WebPage()
{

}

bool WebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, QWebPage::NavigationType type)
{
    if (!frame)
    {
        QDesktopServices::openUrl(request.url());
        return false;
    }
    else
    {
        return QWebPage::acceptNavigationRequest(frame, request, type);
    }
}

