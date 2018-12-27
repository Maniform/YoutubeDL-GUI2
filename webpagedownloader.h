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
    void downloadFinished(QString);

public slots:
    void httpReadyRead();
    void httpFinished();

private:
    bool isReceiving;
    bool httpRequestAborted;
    QUrl url;
    QNetworkReply *reply;
    QString output;
};

#endif // WEBPAGEDOWNLOADER_H
