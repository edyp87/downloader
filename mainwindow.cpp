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
    downloader->download();
}
