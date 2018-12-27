#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include "webpagedownloader.h"
#include "youtubedl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void downloadPressed();
    void downloadFinished(QString);
    void verifierMisesAJourPressed();

private:
    Ui::MainWindow *ui;
    WebPageDownloader webPageDownloader;
    YoutubeDL youtubeDL;
    QFile output;
};

#endif // MAINWINDOW_H
