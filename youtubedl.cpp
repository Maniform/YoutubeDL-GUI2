#include "youtubedl.h"

#ifdef _WIN32
#define OS QString("./")
#elif __LINUX__
#define OS QSrtring("")
#endif

#ifdef QT_DEBUG
#include <QDebug>
#endif

YoutubeDL::YoutubeDL(const QString& _url, const QString& _fichierDestination, const bool& _musiqueSeule, QObject *parent) : QProcess(parent),
    url(_url),
    fichierDestination(_fichierDestination),
    program(OS+"youtube-dl"),
    musiqueSeule(_musiqueSeule),
    corrigerNomFichier(true),
    playlistComplete(false),
    state(NotRunning)
{

}

void YoutubeDL::telecharger()
{

}

void YoutubeDL::verifierMisesAJour()
{
    if(state == NotRunning)
    {
        state = WaitingResult;
        arguments.clear();
        arguments << "--version";
        connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(recevoirVersion()));
        start(program, arguments);
    }
}

void YoutubeDL::recevoirVersion()
{
    QString version(readAll());
    disconnect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(recevoirVersion()));
    state = NotRunning;
    debugPrint(version);
}

void YoutubeDL::debugPrint(QVariant val)
{
#ifdef QT_DEBUG
    qDebug() << val;
#endif
}
