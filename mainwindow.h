#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QNetworkReply;

class Downloader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void download();
    void updateProgressBar(qint64 a, qint64 b);


private:
    void connectProgressBar(QNetworkReply *reply);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
