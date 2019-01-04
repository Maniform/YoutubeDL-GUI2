#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    output.setFileName("out.html");
    connect(ui->actionTelechargerPip, SIGNAL(triggered()), this, SLOT(telechargerPythonAppuye()));
    connect(ui->actionVerifierVersion, SIGNAL(triggered()), this, SLOT(verifierMisesAJourAppuye()));
    connect(&youtubeDL, SIGNAL(estAJour(QString, QString)), this, SLOT(estAJour(QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierMisesAJourAppuye()
{
    youtubeDL.verifierMisesAJour();
}

void MainWindow::telechargerPythonAppuye()
{
    connect(&webPageDownloader, SIGNAL(telechargementTermine(QByteArray)), this, SLOT(pythonTelecharge(QByteArray)));
    connect(&webPageDownloader, SIGNAL(donneesRecues(QByteArray)), this, SLOT(donneesRecues(QByteArray)));
    webPageDownloader.start("https://www.python.org/ftp/python/3.7.2/python-3.7.2.exe");
}

void MainWindow::pythonTelecharge(QByteArray data)
{
    QFile python("python.exe");
    if(python.open(QIODevice::WriteOnly))
    {
        python.write(data);
        python.close();
        QProcess *installPython = new QProcess(this);
        installPython->setProgram("python.exe");
        connect(installPython, SIGNAL(finished(int, QProcess::ExitStatus)), installPython, SLOT(deleteLater()));
        installPython->start();
        QDir().remove("python.exe");
        disconnect(&webPageDownloader, SIGNAL(telechargementTermine(QByteArray)), this, SLOT(pythonTelecharge(QByteArray)));
        disconnect(&webPageDownloader, SIGNAL(donneesRecues(QByteArray)), this, SLOT(donneesRecues(QByteArray)));
    }
}

void MainWindow::imprimerDebug(QVariant val)
{
#ifdef QT_DEBUG
    qDebug() << val;
#endif
}

void MainWindow::donneesRecues(QByteArray data)
{
    editerTailleDonneesTelechargees(data.length());
}

void MainWindow::editerTailleDonneesTelechargees(int value)
{
    ui->label->setText(QString::number(value/1024) + " ko");
}

void MainWindow::estAJour(QString versionActuelle, QString versionInternet)
{
    if(versionActuelle == versionInternet)
    {
        QMessageBox::information(this, "YoutubeDL", "YoutubeDL est à jour.");
    }
    else
    {
        int reponse = QMessageBox::question(this, "YoutubeDL", "Une nouvelle version de YoutubeDL est disponible. La télécharger ?\n(" + versionActuelle + " -> " + versionInternet + ")", QMessageBox::Yes, QMessageBox::No);
        if(reponse == QMessageBox::Yes)
        {
            ui->progressBar->show();
            connect(&youtubeDL, SIGNAL(readyReadStandardOutput()), this, SLOT(imprimerLog()));
            youtubeDL.mettreAJour();
            connect(&youtubeDL, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(miseAJourTerminee(int)));
        }
    }
}

void MainWindow::miseAJourTerminee(int exitCode)
{
    disconnect(&youtubeDL, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(miseAJourTerminee(int, QProcess::ExitStatus)));
    disconnect(&youtubeDL, SIGNAL(readyReadStandardOutput()), this, SLOT(imprimerLog()));
    ui->progressBar->hide();
    if(exitCode == 0)
    {
        QMessageBox::information(this, "YoutubeDL", "Mise à jour de YoutubeDL terminée.");
    }
    else
    {
        QMessageBox::critical(this, "YoutubeDL", "Échec de la mise à jour.");
    }
}

void MainWindow::imprimerLog()
{
    ui->plainTextEdit->appendPlainText(youtubeDL.readAllStandardOutput());
}
