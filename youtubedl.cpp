#include "youtubedl.h"

#ifdef _WIN32
#define OS QString("./")
#elif __LINUX__
#define OS QSrtring("")
#endif

#include <QDebug>

YoutubeDL::YoutubeDL(const QString& _url, const QString& _fichierDestination, const bool& _musiqueSeule, QObject *parent) : QProcess(parent),
    url(_url),
    fichierDestination(_fichierDestination),
    program(OS+"youtube-dl"),
    version("Inconnue"),
    derniereVersion("Inconnue"),
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
        version = "Inconnue";
        derniereVersion = "Inconnue";
        arguments.clear();
        arguments << "--version";
        connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(recevoirVersion()));
        start(program, arguments);
        WebPageDownloader *youtubedlWebsite = new WebPageDownloader("https://rg3.github.io/youtube-dl/download.html");
        connect(youtubedlWebsite, SIGNAL(telechargementTermine(QByteArray)), this, SLOT(recevoirYoutubeDLWebsite(QByteArray)));
        connect(youtubedlWebsite, SIGNAL(telechargementTermine(QByteArray)), youtubedlWebsite, SLOT(deleteLater()));
        youtubedlWebsite->start();
    }
}

void YoutubeDL::recevoirVersion()
{
    version = readAll();
    version.remove('\n');
    version.remove('\r');
    disconnect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(recevoirVersion()));
    if(derniereVersion != "Inconnue")
    {
        state = NotRunning;
        emit(estAJour(version, derniereVersion));
    }
}

void YoutubeDL::recevoirYoutubeDLWebsite(QByteArray site)
{
    derniereVersion = site;
    derniereVersion = derniereVersion.split("/youtube-dl\">")[1].split("</a> (<a href=\"https://yt-dl.org/downloads/")[0];
    if(version != "Inconnue")
    {
        state = NotRunning;
        emit(estAJour(version, derniereVersion));
    }
}

void YoutubeDL::mettreAJour()
{
    if(state == NotRunning)
    {
        state = Running;
        program = "pip install youtube-dl";
        arguments.clear();
        arguments.append("-U");
        connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(miseAJourTerminee()));
        start(program, arguments);
    }
}

void YoutubeDL::miseAJourTerminee()
{
    disconnect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(miseAJourTerminee()));
    arguments.clear();
    program = OS + "youtube-dl";
    state = NotRunning;
}
