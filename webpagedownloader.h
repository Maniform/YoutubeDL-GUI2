#ifndef WEBPAGEDOWNLOADER_H
#define WEBPAGEDOWNLOADER_H

#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>

class WebPageDownloader : public QNetworkAccessManager
{
    Q_OBJECT

public:
    WebPageDownloader(QString="", QObject *parent = Q_NULLPTR);
    WebPageDownloader(QUrl);

    bool start(QString="");
    void setUrl(QString);
    void setUrl(QUrl);

signals:
    void donneesRecues(QByteArray);
    void telechargementTermine(QByteArray);

public slots:
    void httpFinished();
    void readReady();

private:
    bool isReceiving;
    bool httpRequestAborted;
    QUrl url;
    QNetworkReply *reply;
    QByteArray output;
};

#endif // WEBPAGEDOWNLOADER_H
