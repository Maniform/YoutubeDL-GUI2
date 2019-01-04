#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include "webpagedownloader.h"
#include "youtubedl.h"

#include <QVariant>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void verifierMisesAJourAppuye();
    void telechargerPythonAppuye();
    void pythonTelecharge(QByteArray);
    void donneesRecues(QByteArray);
    void estAJour(QString, QString);
    void miseAJourTerminee(int);
    void imprimerLog();

private:
    Ui::MainWindow *ui;
    WebPageDownloader webPageDownloader;
    YoutubeDL youtubeDL;
    QFile output;

    void editerTailleDonneesTelechargees(int value);

    void imprimerDebug(QVariant val);
};

#endif // MAINWINDOW_H
