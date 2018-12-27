#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QProcess>
#include <QString>
#include <QVariant>

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

signals:
    void estAJour(bool);

public slots:
    void recevoirVersion();

private:
    QString url;
    QString fichierDestination;
    QString program;
    QStringList arguments;
    bool musiqueSeule;
    bool corrigerNomFichier;
    bool playlistComplete;
    State state;

    void debugPrint(QVariant val);
};



#endif // YOUTUBEDL_H
