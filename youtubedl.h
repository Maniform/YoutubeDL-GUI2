#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QFile>

#include "webpagedownloader.h"

class YoutubeDL : public QProcess
{
    Q_OBJECT

public:
    enum State{
        NotRunning,
        WaitingResult,
        Running
    };

    YoutubeDL(const QString& _url = "", const QString& _fichierDestination = "", const bool& _musiqueSeule = false, QObject *parent = nullptr);

    void telecharger();
    void verifierMisesAJour();
    void mettreAJour();

signals:
    void estAJour(QString versionActuelle, QString versionInternet);
    void miseAJourTerminee(int);

public slots:
    void recevoirVersion();
    void recevoirYoutubeDLWebsite(QByteArray);
    void miseAJourTerminee();

private:
    QString url;
    QString fichierDestination;
    QString program;
    QString version, derniereVersion;
    QStringList arguments;
    bool musiqueSeule;
    bool corrigerNomFichier;
    bool playlistComplete;
    State state;
};



#endif // YOUTUBEDL_H
