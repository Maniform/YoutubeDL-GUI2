#include "webpagedownloader.h"

WebPageDownloader::WebPageDownloader(QString _url, QObject *parent) : QNetworkAccessManager(parent),
    isReceiving(false),
    url(_url)
{
}

WebPageDownloader::WebPageDownloader(QUrl _url):
    url(_url)
{
}

void WebPageDownloader::setUrl(QString _url)
{
    url = _url;
}

void WebPageDownloader::setUrl(QUrl _url)
{
    url = _url;
}

void WebPageDownloader::httpFinished()
{
    output.append(reply->readAll());
    reply->deleteLater();
    isReceiving = false;
    emit(telechargementTermine(output));
}

void WebPageDownloader::readReady()
{
    output.append(reply->readAll());
    emit(donneesRecues(output));

}

bool WebPageDownloader::start(QString _url)
{
    if(_url != "")
        url = _url;
    if(isReceiving == false)
    {
        output.clear();
        reply = get(QNetworkRequest(url));
        reply->ignoreSslErrors();
        connect(reply, SIGNAL(readyRead()), this, SLOT(readReady()));
        connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
        isReceiving = true;
        return true;
    }
    else
        return false;
}
