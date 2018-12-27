#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    output.setFileName("out.html");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(downloadPressed()));
    connect(&webPageDownloader, SIGNAL(downloadFinished(QString)), this, SLOT(downloadFinished(QString)));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(verifierMisesAJourPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadPressed()
{
    ui->pushButton->setEnabled(false);
    webPageDownloader.setUrl(ui->lineEdit->text());
    webPageDownloader.start();
}

void MainWindow::downloadFinished(QString page)
{
    if(output.open(QIODevice::WriteOnly))
    {
        output.write(page.toUtf8());
        output.close();
    }
    ui->pushButton->setEnabled(true);
}

void MainWindow::verifierMisesAJourPressed()
{
    youtubeDL.verifierMisesAJour();
}
