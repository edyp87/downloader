#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Downloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->downloadButton, &QAbstractButton::released,
                     this, &MainWindow::download);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::download()
{
    QString url = ui->urlEdit->text();
    Downloader *downloader = new Downloader(url, this);
    QNetworkReply *reply = downloader->download();
    connectProgressBar(reply);
}

void MainWindow::updateProgressBar(qint64 a, qint64 b)
{
    if (b > 0)
    {
        qDebug() << "Downloading " << a << "/" << b << "%" << 100.0*((double)a/(double)b);
        ui->progressBar->setValue(100.0*((double)a/(double)b));
    }
}

void MainWindow::connectProgressBar(QNetworkReply *reply)
{
    QObject::connect(reply, &QNetworkReply::downloadProgress,
                     this, &MainWindow::updateProgressBar);
}
