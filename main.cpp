#include "mainwindow.h"
#include <QApplication>
#include <Downloader.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Downloader downloader(QString("http://icons.iconarchive.com/icons/alecive/flatwoken/512/Apps-Qt-icon.png"));
    downloader.download();


    return a.exec();
}
